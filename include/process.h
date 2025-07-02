#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <unordered_map>

struct ProcessInfo
{
    int pid = 0;
    std::string name;
    unsigned long utime = 0;
    unsigned long stime = 0;
    unsigned long long totalTime = 0;
    long rss = 0; // Resident Set Size (pages)
    float cpuUsage = 0.0f;
};

class Process
{
private:
    std::unordered_map<int, ProcessInfo> prevProcesses;
    unsigned long long prevTotalCpuTime = 0;
    int numCores = 1;

    unsigned long long GetTotalCpuTime();

public:
    Process();

    // Update process info and calculate CPU usage
    void Update();

    // Get the top N CPU-consuming processes
    std::vector<ProcessInfo> GetTopProcesses(int topN = 10) const;

    // Get number of CPU cores on system
    int GetNumCores() const { return numCores; }
};

#endif
