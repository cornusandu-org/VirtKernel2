#include "headers.hpp"
#include "trace.hpp"
#include "runproc.hpp"
#include <iostream>

int main(const int argc, const char* argv[]) {
    if (argc == 2) {
        runproc(argv[1]);
    } else {
        std::cerr << "Usage: " << argv[0] << " <path_to_executable>\n";
    }

    exit(0);

    __builtin_unreachable();
}
