#include "exit_.hpp"
#include "headers.hpp"
#include "startup.hpp"

namespace exit_ {
    void (*volatile exit_handler_)() = nullptr;
    void (*volatile exit_handler)(uint64_t) = nullptr;
    void (*volatile panic)(PANIC_) = nullptr;
    volatile const char* exitmsg = nullptr;
}

namespace internal {
    static void L4(PANIC_ reason);

    [[noreturn]] static void L1() {    // exit_handler_
        syscall(SYS_write, 1, exit_::exitmsg, strlen((const char*)exit_::exitmsg));
        exit(0);
        __builtin_unreachable();
    };
    [[noreturn]] static void L2(uint64_t code) {   // exit_handler
        write(1, "Recieved exit code: ", 21);
        std::cout << code << std::endl;
        syscall(SYS_write, 1, exit_::exitmsg, strlen((const char*)exit_::exitmsg));
        exit(0);
        __builtin_unreachable();
    };
    [[noreturn]] static void L3(PANIC_ reason) {    // panic
        write(1, "[CRITICAL] Oops - Panic triggered! Reason code: ", 30);
        std::cout << static_cast<uint64_t>(reason) << std::endl;
        std::cout << "[CRITICAL]" << exit_::exitmsg << std::endl;
        L4(reason);
        exit(1);
        __builtin_unreachable();
    };
    static void L4(PANIC_ reason) {  // Panic code specific functionality/cleanup
        return;
    }

    static I_STARTUPSCHEDULE S1([]() {
        exit_::exit_handler_ = &internal::L1;
        exit_::exit_handler = &internal::L2;
        exit_::panic = &internal::L3;
    });
}
