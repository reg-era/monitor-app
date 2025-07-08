#include "../header.h"

#ifndef MEM_INFO_H
#define MEM_INFO_H

struct MemInfo
{
    float ram_cap;
    float swap_cap;
    float disk_cap;
    float ram_usag;
    float swap_usag;
    float disk_usag;

    MemInfo()
    {
        ram_cap = 16.0;
        swap_cap = 8.0;
        disk_cap = 265.0;
        ram_usag = 0.3;
        swap_usag = 0.1;
        disk_usag = 0.2;
    }

    void update_info()
    {
        ram_usag += 0.001;
        swap_usag += 0.001;
        disk_usag += 0.001;
    }
};

#endif