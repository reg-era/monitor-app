#include "../../include/header.h"

#ifndef TASK_INFO_H
#define TASK_INFO_H

struct TableTask
{
    struct Task
    {
        string pid;
        string name;
        string state;
        float cpu_usage;
        float mem_usage;

        Task(string _pid, string _name, string _state, float _cpu_usage, float _mem_usage)
            : pid(string(_pid)), name(_name), state(_state), cpu_usage(_cpu_usage), mem_usage(_mem_usage) {}
    };

    vector<Task> tasks;

    void update_info()
    {
        unordered_set<string> current_pids;

        for (const filesystem::directory_entry &entry : filesystem::directory_iterator("/proc"))
        {
            string pid = entry.path().filename();
            if (!pid.empty() && all_of(pid.begin(), pid.end(), ::isdigit))
            {
                current_pids.insert(pid);
                vector<TableTask::Task>::iterator it =
                    find_if(
                        tasks.begin(),
                        tasks.end(),
                        [&](const Task &t)
                        { return t.pid == pid; });

                if (it == tasks.end())
                {
                    try
                    {
                        Task new_task = read_pid(pid);
                        tasks.push_back(new_task);
                    }
                    catch (...)
                    {
                        printf("process:%s read info lost\n", pid.c_str());
                    }
                }
            }
        }

        // Remove tasks that no longer exist
        tasks.erase(remove_if(
                        tasks.begin(),
                        tasks.end(),
                        [&](const Task &t)
                        { return current_pids.find(t.pid) == current_pids.end(); }),
                    tasks.end());
    }

    Task read_pid(const string &pid)
    {
        string name, state;
        float cpu_usage = 0.0f, mem_usage = 0.0f;

        // Read /proc/[pid]/stat once
        ifstream stat_file("/proc/" + pid + "/stat");
        if (stat_file)
        {
            string line;
            getline(stat_file, line);
            istringstream iss(line);
            string field;
            vector<string> fields;

            while (iss >> field)
                fields.push_back(field);

            if (fields.size() > 15)
            {
                name = fields[1]; // Might still contain parentheses
                state = fields[2];
                float utime = stof(fields[13]);
                float stime = stof(fields[14]);
                cpu_usage = utime + stime; // Just a raw tick count
            }
        }

        // Remove parentheses from name
        if (!name.empty() && name.front() == '(' && name.back() == ')')
            name = name.substr(1, name.size() - 2);

        // Read memory usage from /status
        ifstream status_file("/proc/" + pid + "/status");
        string line;
        while (getline(status_file, line))
        {
            if (line.find("VmRSS:") == 0)
            {
                istringstream iss(line.substr(6));
                float mem_kb;
                iss >> mem_kb;
                mem_usage = mem_kb / 1024.0f;
                break;
            }
        }

        return Task(pid, name, state, cpu_usage, mem_usage);
    }

    int count_tasks()
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
        return count;
    }
};

#endif