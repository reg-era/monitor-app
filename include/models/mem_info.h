#include "../header.h"

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
        string key;
        unsigned long value;
        ifstream file("/proc/meminfo");
        string line;

        while (getline(file, line))
        {
            istringstream ss(line);
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
            cerr << "Failed to open /sys/block" << endl;
            return;
        }

        struct dirent *entry;

        float disk_tot, disk_usg = 0;
        // Iterate through all devices in /sys/block
        while ((entry = readdir(dir)) != nullptr)
        {
            string device = "/dev/" + string(entry->d_name);

            // Skip non-disk entries like "loop", "ram" devices, etc.
            if (device.find("loop") != string::npos || device.find("ram") != string::npos)
            {
                continue;
            }

            struct statvfs buf;
            if (statvfs(device.c_str(), &buf) != 0)
            {
                cerr << "Failed to get stats for device: " << device << endl;
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

    static string format_size(float cap)
    {
        const char *units[] = {"KB", "MB", "GB", "TB"};
        int unit_index = 0;

        while (cap >= 1024.0f && unit_index < 3)
        {
            cap /= 1024.0f;
            unit_index++;
        }

        ostringstream formatted_size;
        formatted_size << fixed << setprecision(2) << cap << " " << units[unit_index];

        return formatted_size.str();
    }
};

#endif
