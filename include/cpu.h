#ifndef cpu_H
#define cpu_H

struct CpuCore
{
    unsigned long long prevUser = 0;
    unsigned long long prevNice = 0;
    unsigned long long prevSystem = 0;
    unsigned long long prevIdle = 0;
    float usage = 0.;
};

struct SystemInfo
{
    std::string UserName;
    std::string HostName;
    std::string CpuName;
    std::string CpuType;
};

class CPU
{
private:
    std::string fileData = "/proc/stat";
    std::vector<CpuCore> cores;
    double frameTime;
    double updateInterval;

public:
    SystemInfo sysInfo;

    CPU(double time);

    void update(double time);
    int getCoreCount() const;
    float getCoreUsage(int index) const;
    const std::vector<CpuCore> &getCores() const;
    void LoadSystemInfo();
};
#endif