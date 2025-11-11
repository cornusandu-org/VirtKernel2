#pragma once

#include "headers.hpp"

struct ProcData {
    pid_t pid;
    pid_t internalpid;
    uint64_t privilege;
    uint8_t ring = 3;

    void terminate();
};

struct KernelStructure : ProcData {
    pid_t pid;
    pid_t internalpid;
    uint64_t privilege;
    uint8_t ring = 0;

    void terminate();
};

std::vector<ProcData> proc_list;

ProcData& launch_proc(const char* const path);
// TODO: void escalate_proc(uint64_t new_privilege);
// TODO: void escalate_proc(uint64_t new_privilege, uint8_t new_ring);
