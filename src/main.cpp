#include "headers.hpp"
#include "trace.hpp"
#include <iostream>

uint8_t errcode = EXIT_SUCCESS;

void _setup() {
    _setup_L1();
}

void cf_exit() {
    if (errcode == EXIT_DEBUG0 || errcode == EXIT_DEBUG1 || errcode == EXIT_DEBUG2 || errcode == EXIT_DEBUG3) {
        if (!DEBUG_BUILD) {return;}

        std::cerr << "[DEXIT] DEBUG EXIT TRIGGERED (ID=" << errcode - EXIT_DEBUG0 << ")" << std::endl;
        exit(errcode);
    }
    switch (errcode) {
        case EXIT_SUCCESS: {
            goto _finish;
        }
        case EXIT_FAILURE: {
            std::cerr << "[UEXIT] An unknown error occured. Stopping the program. (EXIT CODE " << errcode << ")" << std::endl;
            goto _finish;
        }
        case EXIT_NO_SO: {
            std::cerr << "[EXIT] We failed to load a dynamic library. (EXIT CODE " << errcode << ")" << std::endl;
            goto _finish;
        }
        case EXIT_SEG_FAULT: {
            std::cerr << "[EXIT] Oops! Looks like a segfault (program memory was corrupted, or the program attempted to access invalid memory) (EXIT CODE " << errcode << ")" << std::endl;
            goto _finish;
        }
        case EXIT_PANIC: {
            std::cerr << "[UEXIT] Oops! Looks like something went wrong, and the program had to halt. (EXIT CODE " << errcode << ")" << std::endl;
            goto _finish;
        }
        case EXIT_FORCED: {
            std::cerr << "[EEXIT] Oops! Looks like you killed me. (EXIT_FORCED by SIGTERM / SIGILL)" << std::endl;
            goto _finish;
        }
        case EXIT_REQUESTED: {
            std::cerr << "[EEXIT] Oops! Looks like you killed me. (EXIT_REQUESTED)" << std::endl;
            goto _finish;
        }
        case EXIT_TERMINATED_BY_KERNEL: {
            std::cerr << "[KEXIT] Looks like the Linux kernel is attempting to kill me. (Error code: " << errcode << "/EXIT_TERMINATED_BY_KERNEL)" << std::endl;
            goto _finish;
        }
        default: {
            std::cerr << "[UEXIT] An unknown error occured, and no pre-defined exit code was found. (EXIT CODE " << errcode << ")" << std::endl;
            goto _finish;
        }
    }
    _finish:
        exit(errcode);
}

int main() {
    _setup();

    pid_t pid = fork();
    if (pid == 0) {
        std::cerr << "Pid 0\n";
        errcode = EXIT_SEG_FAULT; goto exit_proc;
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl("./test", nullptr);
    } else {
        std::cerr << "PID != 0\n";
        errcode = EXIT_SEG_FAULT; goto exit_proc;
        trace::trace_child(pid);
    }

    exit_proc:
        exit(errcode);

    __builtin_unreachable();
}
