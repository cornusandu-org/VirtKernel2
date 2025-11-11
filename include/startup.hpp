#pragma once

#include "headers.hpp"
#include <functional>

struct I_STARTUPSCHEDULE {
    I_STARTUPSCHEDULE(std::function<void()> func);
};
