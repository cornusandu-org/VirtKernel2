#pragma once
#include <cstdint>

//#define EXIT_SEG_FAULT 139  // SIGSEGV / SIGBUS / SIGPIPE
//#define EXIT_NO_SO 15
//#define EXIT_DEBUG0 16
//#define EXIT_DEBUG1 17
//#define EXIT_DEBUG2 18
//#define EXIT_DEBUG3 19

enum class EXIT_ : uint64_t {
    EXIT_SEG_FAULT = 139,
    EXIT_NO_SO = 15,
    EXIT_DEBUG0 = 16,
    EXIT_DEBUG1 = 17,
    EXIT_DEBUG2 = 18,
    EXIT_DEBUG3 = 19
};

enum class PANIC_ {
    PANIC_LINUXINTER = 1, // Linux Intervention
    PANIC_ROGUECHILD = 2,  // Rogue Child (attempts to bypass isolation)
    PANIC_ISOLATIONIMPOSSIBLE = 3
};

namespace exit_ {
    extern void(*volatile exit_handler_)();
    extern void(*volatile exit_handler)(uint64_t exitcode);
    extern void(*volatile panic)(PANIC_ reason);
    extern volatile const char* exitmsg;  // Use MADV_DONTFORK to allocate memory that fork()-ed processes dont get access to
}
