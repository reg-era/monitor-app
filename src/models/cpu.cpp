#include "../../../include/header.h"
#include "../../../include/cpu.h"

CPU::CPU(double time)
{
    update(time);
    LoadSystemInfo();
}

void CPU::update(double time)
{
    if (time < frameTime + updateInterval && frameTime != 0)
    {
        return;
    }

    frameTime = time;

    std::ifstream file(fileData);
    std::string line;

    if (!file.is_open())
        return;

    int index = 0;
    while (std::getline(file, line))
    {
        if (line.substr(0, 3) != "cpu")
            break;

        std::istringstream ss(line);
        std::string label;
        unsigned long long user, nice, system, idle;
        ss >> label >> user >> nice >> system >> idle;

        if (label == "cpu")
            continue; // Skip total line

        if ((long unsigned int)index >= cores.size())
            cores.push_back(CpuCore());

        auto &core = cores[index];

        unsigned long long prevTotal = core.prevUser + core.prevNice + core.prevSystem + core.prevIdle;
        unsigned long long currTotal = user + nice + system + idle;

        unsigned long long totalDiff = currTotal - prevTotal;
        unsigned long long idleDiff = idle - core.prevIdle;

        core.usage = (totalDiff > 0) ? 100.0f * (1.0f - (float)idleDiff / totalDiff) : 0.0f;

        core.prevUser = user;
        core.prevNice = nice;
        core.prevSystem = system;
        core.prevIdle = idle;

        ++index;
    }
}

int CPU::getCoreCount() const
{
    return cores.size();
}

float CPU::getCoreUsage(int index) const
{
    if (index < 0 || index >= (int)cores.size())
        return 0.0f;
    return cores[index].usage;
}

const std::vector<CpuCore> &CPU::getCores() const
{
    return cores;
}

void CPU::LoadSystemInfo()
{
    SystemInfo info;

    // 1. Get the logged-in user name
    const char *user = getlogin();
    info.UserName = user ? std::string(user) : "Unknown";

    // 2. Get the hostname
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) == 0)
        info.HostName = std::string(hostname);
    else
        info.HostName = "Unknown";

    // 3. Get CPU name and type from /proc/cpuinfo
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    std::string line;

    while (std::getline(cpuInfoFile, line))
    {
        if (line.find("model name") != std::string::npos && info.CpuName.empty())
        {
            size_t colon = line.find(":");
            info.CpuName = line.substr(colon + 2); // Skip ": "
        }

        if (line.find("vendor_id") != std::string::npos && info.CpuType.empty())
        {
            size_t colon = line.find(":");
            info.CpuType = line.substr(colon + 2); // Skip ": "
        }

        // Stop reading if both fields are filled
        if (!info.CpuName.empty() && !info.CpuType.empty())
            break;
    }

    sysInfo = info;
}

// void CPU::UpdateThermalAndFan()
// { // Thermal check
    // std::ifstream tempFile("/sys/class/thermal/thermal_zone0/temp");
    // if (tempFile.is_open())
    // {
        // int tempMilliC = 0;
        // tempFile >> tempMilliC;
        // thermal.temperatureC = tempMilliC / 1000.0f;
    // }
    // else
    // {
        // thermal.temperatureC = 0.0f; // fallback to safe value
    // }
// 
    // Fan check
    // fan.active = false; // default to false
    // for (int i = 0; i < 5; ++i)
    // {
        // std::string base = "/sys/class/hwmon/hwmon" + std::to_string(i);
        // std::ifstream fanFile(base + "/fan1_input");
        // if (fanFile.is_open())
        // {
            // fan.active = true;
            // fanFile >> fan.speedRPM;
// 
            // if (fan.speedRPM > 3000)
                // fan.level = 3;
            // else if (fan.speedRPM > 1500)
                // fan.level = 2;
            // else if (fan.speedRPM > 500)
                // fan.level = 1;
            // else
                // fan.level = 0;
// 
            // break;
        // }
    // }
// }
