#include "startup.hpp"

I_STARTUPSCHEDULE::I_STARTUPSCHEDULE(std::function<void()> func) {
    func();
}
