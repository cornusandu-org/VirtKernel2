#pragma once
#include "headers.hpp"

namespace trace {
    void(*trace_child)(pid_t pid) = nullptr;
}

inline void _setup_L1() {
    using namespace trace;

    auto library = dlopen("./trace.so", RTLD_LAZY | RTLD_LOCAL);

    if (library == NULL) {
        goto error;
    }

    trace_child = (void(*)(pid_t)) dlsym(library, "trace_child");

    if (trace_child == NULL || dlerror() != NULL) {
        goto error;
    }

    return;

    error:
        std::cerr << "Failed to load a dynamic library (trace.so).\n";
        exit(1);
    
    __builtin_unreachable();
}
