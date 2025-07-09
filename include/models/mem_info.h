#include "../header.h"
#include <fstream>
#include <sstream>
#include <string>

#ifndef MEM_INFO_H
#define MEM_INFO_H

struct MemInfo
{
    unsigned long mem_total;
    unsigned long mem_free;
    unsigned long mem_buffr;
    unsigned long mem_cach;
    unsigned long swap_cap;
    unsigned long swap_usag;
    unsigned long disk_cap;
    unsigned long disk_usag;

    MemInfo()
    {
        mem_total = 0.0;
        swap_cap = 0.0;
        disk_cap = 0.0;
        swap_usag = 0.0;
        disk_usag = 0.0;
    }

    void update_info()
    {
        std::string key;
        unsigned long value;
        std::ifstream file("/proc/meminfo");
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            ss >> key >> value;

            if (key == "MemTotal:")
            {
                mem_total = value;
            }
            else if (key == "MemFree:")
            {
                mem_free = value;
            }
            else if (key == "Buffers:")
            {
                mem_buffr = value;
            }
            else if (key == "Cached:")
            {
                mem_cach = value;
            }
            else if (key == "SwapTotal:")
            {
                swap_cap = value;
            }
            else if (key == "SwapUsed:")
            {
                swap_usag = value;
            }
        }

        DIR *dir = opendir("/sys/block");
        if (dir == nullptr)
        {
            std::cerr << "Failed to open /sys/block" << std::endl;
            return;
        }

        struct dirent *entry;

        float disk_tot, disk_usg = 0;
        // Iterate through all devices in /sys/block
        while ((entry = readdir(dir)) != nullptr)
        {
            std::string device = "/dev/" + std::string(entry->d_name);

            // Skip non-disk entries like "loop", "ram" devices, etc.
            if (device.find("loop") != std::string::npos || device.find("ram") != std::string::npos)
            {
                continue;
            }

            struct statvfs buf;
            if (statvfs(device.c_str(), &buf) != 0)
            {
                std::cerr << "Failed to get stats for device: " << device << std::endl;
                return;
            }

            // Total disk capacity in bytes
            unsigned long long total_size = buf.f_frsize * buf.f_blocks;
            // Used space in bytes
            unsigned long long used_space_bytes = total_size - (buf.f_frsize * buf.f_bfree);

            disk_tot += total_size / 1024.0;
            disk_usg += used_space_bytes / 1024.0;
        }

        disk_cap = disk_tot;
        disk_usag = disk_usg;
        closedir(dir);
    }
};

#endif
