#include "headers.hpp"
#include "trace.hpp"
#include "exit_.hpp"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

namespace dcinternal {

    inline bool is_syscall_stop(int status) {
        // Detect syscall-stop (SIGTRAP|0x80)
        return WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80);
    }

    inline int ptrace_event(int status) {
        // Extract ptrace event code (if any)
        return (status >> 16) & 0xffff;
    }

    inline bool try_sysemu(pid_t pid) {
        // Try to use PTRACE_SYSEMU; return true if supported
        if (ptrace(PTRACE_SYSEMU, pid, nullptr, nullptr) == -1) {
            return !(errno == EINVAL || errno == ENOSYS);
        }
        return true;
    }
}

namespace internal {
    static void E1() {

    }
}

namespace trace {

    void trace_child(pid_t pid) {
        int status;
        waitpid(pid, &status, 0);

        // Set basic tracing options
        ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

        // Detect if PTRACE_SYSEMU works
        bool have_sysemu = dcinternal::try_sysemu(pid);
        if (!have_sysemu) {
            exit_::exitmsg = "PTRACE_SYSEMU not supported on this system.\n";
            exit_::panic(PANIC_::PANIC_LINUXINTER);
            //std::cerr << "Warning: PTRACE_SYSEMU unsupported, syscalls will execute normally.\n";
            //ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
        }

        bool in_syscall = false;

        while (true) {
            if (waitpid(pid, &status, 0) < 0) break;
            if (WIFEXITED(status)) break;

            if (dcinternal::is_syscall_stop(status)) {
                user_regs_struct regs{};
                ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

                if (!in_syscall) {
                    in_syscall = true;
                    std::cout << "[enter] syscall " << regs.orig_rax << std::endl;

                    
                    if (regs.orig_rax == SYS_write) {
                        size_t len = regs.rdx;
                        std::vector<char> buf(len);
                    
                        // safer and faster than ptrace loop
                        struct iovec local_iov{ buf.data(), len };
                        struct iovec remote_iov{ reinterpret_cast<void*>(regs.rsi), len };
                        ssize_t n = process_vm_readv(pid, &local_iov, 1, &remote_iov, 1, 0);
                        if (n < 0) {
                            perror("process_vm_readv");
                        } else {
                            // emulate the write
                            write((int)regs.rdi, "[USER OUTPUT]\0", 13);
                            write((int)regs.rdi, buf.data(), n);
                        }
                    
                        // Optionally modify return value in child regs
                        regs.rax = n;
                        ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
                    }

                    // Example decision: don’t execute syscall in kernel
                    if (have_sysemu)
                        ptrace(PTRACE_SYSEMU, pid, nullptr, nullptr);
                    else
                        ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
                } else {
                    in_syscall = false;
                    std::cout << "[exit] syscall " << regs.orig_rax
                              << " -> " << regs.rax << std::endl;

                    if (regs.orig_rax == 60) {
                        std::cout << "[USER] exit(" << regs.rdi << ")\n";
                        ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
                        kill(pid, SIGKILL);
                    }

                    if (have_sysemu)
                        ptrace(PTRACE_SYSEMU, pid, nullptr, nullptr);
                    else
                        ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
                }
                continue;
            }

            if (WIFSTOPPED(status)) {
                int event = dcinternal::ptrace_event(status);
                if (event)
                    std::cout << "[event] code " << event << std::endl;
                ptrace(PTRACE_CONT, pid, nullptr, nullptr);
            }
        }
    }

}
