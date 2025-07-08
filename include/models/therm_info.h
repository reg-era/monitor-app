#include "../../include/header.h"

#ifndef THERM_INFO_H
#define THERM_INFO_H

struct ThermalInfo
{
    int option;
    int fps;
    int scale;
    int cpu_count;
    float cpu_diag[90];
    int tem_count;
    float tem_diag[90];
    int fan_count;
    float fan_diag[90];

    ThermalInfo()
    {
        option = 0;
        fps = 50;
        scale = 50;
        cpu_count = 0;
        tem_count = 0;
        fan_count = 0;
    }

    void update_info()
    {
        switch (option)
        {
        case 0:
            cpu_diag[cpu_count] = sinf(cpu_count * 0.1f);
            cpu_count = (cpu_count + 1) % 90;
            break;
        case 1:
            tem_diag[tem_count] = cosf(tem_count * 0.1f);
            tem_count = (tem_count + 1) % 90;
            break;
        case 2:
            fan_diag[fan_count] = tanf(fan_count * 0.1f);
            fan_count = (fan_count + 1) % 90;
            break;
        }
    }
};

#endif