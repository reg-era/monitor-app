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
        string cpu_usage;
        string mem_usage;

        Task(string _pid, string _name, string _state, string _cpu_usage, string _mem_usage)
            : pid(string(_pid)), name(_name), state(_state), cpu_usage(_cpu_usage), mem_usage(_mem_usage) {}
    };

    std::vector<Task> tasks;
    string search;

    void update_info()
    {
        // tasks.push_back(Task("122", "name", "one", "10", "20"));
    }
};

#endif