#include "headers.hpp"
#include "trace.hpp"
#include <iostream>

namespace trace {
    void trace_child(pid_t pid) {
        int status;

        // Wait for the child to stop on exec
        waitpid(pid, &status, 0);

        // Set options for syscall tracing
        ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

        // Start tracing syscalls
        ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);

        while (true) {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) break;

            user_regs_struct regs{};
            ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

            std::cout << "Syscall: " << regs.orig_rax << std::endl;

            ptrace(PTRACE_SYSCALL, pid, nullptr, nullptr);
        }
    }
}
