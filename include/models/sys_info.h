#include "../../include/header.h"

#ifndef SYS_INFO_H
#define SYS_INFO_H

struct SysInfo
{
    string os_name;
    string host_name;
    string usr_name;
    string cpu_name;
    int tasks;

    SysInfo()
    {
        os_name = "Linux";
        host_name = "129.0.0.1";
        usr_name = "Regera";
        cpu_name = "i5 Wiw";
        tasks = 3;
    }

    void update_info()
    {
        tasks = tasks + 1;
    }
};

#endif