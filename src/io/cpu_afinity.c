#define _GNU_SOURCE
#include <sched.h>
#include "../binder.h"

void setCPU(i32 core)
{
    cpu_set_t cpusetp;
    __CPU_ZERO_S(sizeof(cpu_set_t), &cpusetp);      // CPU_ZERO(&mask);
    __CPU_SET_S(core, sizeof(cpu_set_t), &cpusetp); // CPU_SET(core, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpusetp);
}
