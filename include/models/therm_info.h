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
    bool fans_notfound = false;

    float update_interval = 0.01f; // seconds per update at 100 fps (1/100)
    float time_accumulator = 0.0f;

    ThermalInfo()
    {
        option = 0;
        fps = 50;
        scale = 50;
        cpu_count = 0;
        tem_count = 0;
        fan_count = 0;
    }

    void update_info(float delta_time)
    {
        if (fps <= 0)
            return;

        update_interval = 1.0f / fps;
        time_accumulator += delta_time;

        if (time_accumulator >= update_interval)
        {
            time_accumulator -= update_interval;
            switch (option)
            {
            case 0:
                shift_and_append(cpu_diag, get_cpu_usage() + scale / 100.0f);
                break;
            case 1:
                shift_and_append(tem_diag, (get_temperature() + scale - 100) / 100.0f);
                break;
            case 2:
                float fanspeed = get_fan_speed();
                if (!fans_notfound)
                    shift_and_append(fan_diag, fanspeed + scale / 100.0f);
                break;
            }
        }
    }

    void shift_and_append(float *array, float new_value)
    {
        for (int i = 1; i < 90; ++i)
        {
            array[i - 1] = array[i];
        }
        array[90 - 1] = new_value;
    }

    float get_temperature()
    {
        // Try thermal_zone files
        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator("/sys/class/thermal"))
        {
            const std::filesystem::path &path = entry.path();
            if (path.filename().string().find("thermal_zone") != std::string::npos)
            {
                std::ifstream type_file(path / "type");
                std::string type;
                if (type_file >> type)
                {
                    if (type.find("x86_pkg_temp") != std::string::npos)
                    {
                        std::ifstream temp_file(path / "temp");
                        int millidegree;
                        if (temp_file >> millidegree)
                        {
                            return millidegree / 1000.0f;
                        }
                    }
                }
            }
        }
        return -1.0f;
    }

    float get_cpu_usage()
    {
        static long prev_idle = 0, prev_total = 0;

        std::ifstream stat("/proc/stat");
        std::string cpu;
        long user, nice, system, idle, iowait, irq, softirq;

        stat >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

        long idle_time = idle + iowait;
        long total_time = user + nice + system + idle + iowait + irq + softirq;

        long delta_idle = idle_time - prev_idle;
        long delta_total = total_time - prev_total;

        prev_idle = idle_time;
        prev_total = total_time;

        if (delta_total == 0)
            return 0.0f; // avoid divide by zero

        return (1.0f - (float)delta_idle / delta_total);
    }

    float get_fan_speed()
    {
        if (fans_notfound)
            return 0.0f;
        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator("/sys/class/hwmon"))
        {
            const std::filesystem::path &path = entry.path();
            for (int i = 1; i <= 5; ++i)
            {
                std::ifstream fan_file(path / ("fan" + std::to_string(i) + "_input"));
                int rpm;
                if (fan_file >> rpm)
                {
                    if (rpm > 0)
                        return static_cast<float>(rpm); // return first valid fan speed
                }
            }
        }
        fans_notfound = true;
        return 0.0f;
    }
};

#endif