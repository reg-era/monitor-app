#include  "../../../include/process.h"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <algorithm>
#include <unistd.h> // for sysconf
#include <limits>  

// Helper function: read total CPU jiffies from /proc/stat
unsigned long long Process::GetTotalCpuTime()
{
    std::ifstream file("/proc/stat");
    if (!file.is_open())
        return 0;

    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;

    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    return user + nice + system + idle + iowait + irq + softirq + steal;
}

Process::Process()
{
    numCores = sysconf(_SC_NPROCESSORS_ONLN);
    prevTotalCpuTime = GetTotalCpuTime();
}

void Process::Update()
{
    unsigned long long totalCpuTime = GetTotalCpuTime();
    unsigned long long totalCpuDiff = totalCpuTime - prevTotalCpuTime;
    prevTotalCpuTime = totalCpuTime;

    DIR* proc = opendir("/proc");
    if (!proc)
        return;

    std::unordered_map<int, ProcessInfo> currentProcesses;

    struct dirent* entry;
    while ((entry = readdir(proc)) != nullptr)
    {
        if (!isdigit(entry->d_name[0]))
            continue;

        int pid = atoi(entry->d_name);
        std::string statPath = "/proc/" + std::to_string(pid) + "/stat";

        std::ifstream statFile(statPath);
        if (!statFile.is_open())
            continue;

        std::string line;
        std::getline(statFile, line);
        statFile.close();

        std::istringstream ss(line);

        int pidFromStat;
        std::string comm;
        char state;
        unsigned long utime, stime;
        long rss;

        // Parsing /proc/[pid]/stat
        // The second field is comm (process name) surrounded by parentheses and can contain spaces
        // So we extract it carefully

        ss >> pidFromStat;

        // Extract comm between parentheses
        size_t start = line.find('(');
        size_t end = line.find(')');
        if (start == std::string::npos || end == std::string::npos || end <= start)
            continue;
        comm = line.substr(start + 1, end - start - 1);

        // Move stream position to after comm
        std::string afterComm = line.substr(end + 2); // +2 to skip ") "
        std::istringstream ss2(afterComm);

        ss2 >> state;

        // Skip fields until utime (14) and stime (15)
        // Fields after pid and comm: state (1), ppid (2), pgrp (3), session (4), tty_nr (5), tpgid (6), flags (7), minflt (8), cminflt (9), majflt (10), cmajflt (11)
        // utime (14) = 11th field after state, stime (15) = 12th field after state
        for (int i = 0; i < 11; ++i)
            ss2.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

        ss2 >> utime >> stime;

        // Skip to rss (24) which is 9 fields after stime
        for (int i = 0; i < 9; ++i)
            ss2.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

        ss2 >> rss;

        unsigned long long totalTime = utime + stime;

        ProcessInfo procInfo;
        procInfo.pid = pidFromStat;
        procInfo.name = comm;
        procInfo.utime = utime;
        procInfo.stime = stime;
        procInfo.totalTime = totalTime;
        procInfo.rss = rss;

        // Calculate CPU usage percentage
        if (prevProcesses.count(pid) > 0)
        {
            unsigned long long prevTotal = prevProcesses[pid].totalTime;
            unsigned long long delta = totalTime - prevTotal;
            if (totalCpuDiff > 0)
            {
                procInfo.cpuUsage = 100.0f * (float)delta / (float)totalCpuDiff * numCores;
            }
        }
        else
        {
            procInfo.cpuUsage = 0.0f;
        }

        currentProcesses[pid] = procInfo;
    }

    closedir(proc);

    prevProcesses = std::move(currentProcesses);
}

std::vector<ProcessInfo> Process::GetTopProcesses(int topN) const
{
    std::vector<ProcessInfo> processes;
    for (const auto& pair : prevProcesses)
        processes.push_back(pair.second);

    std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b) {
        return a.cpuUsage > b.cpuUsage;
    });

    if ((int)processes.size() > topN)
        processes.resize(topN);

    return processes;
}
