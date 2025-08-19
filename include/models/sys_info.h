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
        // Get OS Name
        ifstream os_file("/etc/os-release");
        string line;
        while (getline(os_file, line))
        {
            if (line.find("NAME=") == 0)
            {
                int start = line.find("\"");
                int end = line.rfind("\"");
                if (start != string::npos && end != string::npos && end > start)
                {
                    os_name = line.substr(start + 1, end - start - 1);
                }
                break;
            }
        }

        // Get Hostname
        ifstream host_file("/proc/sys/kernel/hostname");
        getline(host_file, host_name);

        // Get Username
        struct passwd *pw = getpwuid(geteuid());
        usr_name = pw ? pw->pw_name : "unknown";

        // Get CPU name
        ifstream cpu_file("/proc/cpuinfo");
        while (getline(cpu_file, line))
        {
            if (line.find("model name") == 0)
            {
                int pos = line.find(":");
                if (pos != string::npos)
                {
                    cpu_name = line.substr(pos + 2);
                }
                break;
            }
        }

        tasks = 0;
    }

    void update_info()
    {
        int count = 0;
        for (const filesystem::directory_entry &entry : filesystem::directory_iterator("/proc"))
        {
            string name = entry.path().filename();
            if (!name.empty() && all_of(name.begin(), name.end(), ::isdigit))
            {
                count++;
            }
        }
        tasks = count;
    }
};

#endif
