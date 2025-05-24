#include "header.h"

#ifndef memory_h
#define memory_h
class Memory
{
public:
    unsigned long long totalRAM = 0; // in KB
    unsigned long long freeRAM = 0;  // in KB
    unsigned long long usedRAM = 0;  // in KB

    unsigned long long totalSwap = 0; // in KB
    unsigned long long freeSwap = 0;  // in KB
    unsigned long long usedSwap = 0;  // in KB

    unsigned long long totalDisk = 0; // in bytes
    unsigned long long freeDisk = 0;  // in bytes
    unsigned long long usedDisk = 0;  // in bytes;

    Memory(double time);
    void update();

private:
    unsigned long long parseLineValue(const std::string &line);
};
#endif
