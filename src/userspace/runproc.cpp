#include "headers.hpp"
#include "trace.hpp"
#include "runproc.hpp"
#include <string>

void runproc(const char* const path) {
    pid_t pid = fork();
    if (pid == 0) {
        std::cerr << "Pid 0\n";
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(path, path, (char*)nullptr);
        perror("execl failed");   // <— add this
        exit(1);
    } else {
        std::cerr << "PID != 0\n";
        trace::trace_child(pid);
    }
}
