#include "headers.hpp"
#include "trace.hpp"

namespace trace {
    void trace_child(pid_t pid) {
        int status;
        while (true) {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) break;

            user_regs_struct regs{};
            ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

            long syscall = regs.orig_rax; // On x86-64

            // Example: block write(1, ...) for demonstration
            if (syscall == 1 && regs.rdi == 1) {
                regs.orig_rax = -1; // fake invalid syscall
                ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
            }

            ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
        }
    };
}