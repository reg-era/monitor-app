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

// struct ThermalInfo
// {
    // float temperatureC = 0.0f; // in Celsius
// };
// 
// struct FanInfo
// {
    // bool active = false;
    // int speedRPM = 0; // Fan speed in RPM
    // int level = 0;    // Optional: custom mapped level (e.g., 1–3)
// };

class CPU
{
private:
    std::string fileData = "/proc/stat";
    std::vector<CpuCore> cores;
    double frameTime;
    double updateInterval;

    // ThermalInfo thermal; // <-- These were missing
    // FanInfo fan;         // <-- These were missing

public:
    SystemInfo sysInfo;

    CPU(double time);

    void update(double time);
    void LoadSystemInfo();
    // void UpdateThermalAndFan(); // <-- Add this

    int getCoreCount() const;
    float getCoreUsage(int index) const;
    const std::vector<CpuCore> &getCores() const;

    // Accessors
    // ThermalInfo getThermalInfo() const { return thermal; }
    // FanInfo getFanInfo() const { return fan; }
};
#endif