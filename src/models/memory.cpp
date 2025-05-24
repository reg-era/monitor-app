#include "../../../include/memory.h"

Memory::Memory(double time)
{
    printf("%f", time);
    update();
}

void Memory::update()
{
    std::ifstream memFile("/proc/meminfo");
    std::string line;

    unsigned long long memTotal = 0, memFree = 0, buffers = 0, cached = 0, swapTotal = 0, swapFree = 0;

    while (std::getline(memFile, line))
    {
        if (line.find("MemTotal:") == 0)
            memTotal = parseLineValue(line);
        else if (line.find("MemFree:") == 0)
            memFree = parseLineValue(line);
        else if (line.find("Buffers:") == 0)
            buffers = parseLineValue(line);
        else if (line.find("Cached:") == 0)
            cached = parseLineValue(line);
        else if (line.find("SwapTotal:") == 0)
            swapTotal = parseLineValue(line);
        else if (line.find("SwapFree:") == 0)
            swapFree = parseLineValue(line);
    }

    totalRAM = memTotal;
    freeRAM = memFree + buffers + cached;
    usedRAM = memTotal - freeRAM;

    totalSwap = swapTotal;
    freeSwap = swapFree;
    usedSwap = swapTotal - freeSwap;

    // struct statvfs stat;
    // totalDisk = stat.f_blocks * stat.f_frsize;
    // freeDisk = stat.f_bfree * stat.f_frsize;
    // usedDisk = totalDisk - freeDisk;
}

unsigned long long Memory::parseLineValue(const std::string &line)
{
    size_t start = line.find_first_of("0123456789");
    size_t end = line.find(" kB");
    if (start != std::string::npos && end != std::string::npos)
        return std::stoull(line.substr(start, end - start));
    return 0;
}
