#include "procmanager.hpp"
#include "headers.hpp"
#include "runproc.hpp"

#include <thread>

void ProcData::terminate() {
    if (!(pid > 1 && internalpid != 0 && ring != 0)) {
        return;
    }

    kill(pid, SIGKILL);
};

void KernelStructure::terminate() {  // Do nothing
    return;
};

ProcData& launch_proc(const char* const path) {
    pid_t pid = 0;
    std::thread t([](const char* const p, pid_t* pp) {
        runproc(p, pp);
    }, path, &pid);
    t.detach();

    ProcData p;
    p.pid = pid;
    p.internalpid = proc_list.size();
    p.privilege = 0;
    p.ring = 3;
    proc_list.push_back(p);
    return proc_list.back();
}
