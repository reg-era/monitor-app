#include "../../include/graphic_ui.h"
#include <iostream>
#include <vector>
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

void DrawTaskSection(float width, float height)
{
    static TableTask table_task;
    table_task.update_info();

    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::BeginChild("Middle", ImVec2(width, height), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Task Process Information");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    static char searchText[128] = "";
    ImGui::Text("Search (PID or name)");
    ImGui::SameLine();
    ImGui::InputText("", searchText, IM_ARRAYSIZE(searchText));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    if (ImGui::BeginTable("Table Example", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("PID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("State");
        ImGui::TableSetupColumn("CPU usage");
        ImGui::TableSetupColumn("Memory usage");

        ImGui::TableHeadersRow();

        for (int i = 0; i < int(table_task.tasks.size()); i++)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(table_task.tasks[i].pid.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(table_task.tasks[i].name.c_str());
            ImGui::TableSetColumnIndex(2);
            ImGui::Text(table_task.tasks[i].state.c_str());
            ImGui::TableSetColumnIndex(3);
            ImGui::Text(table_task.tasks[i].cpu_usage.c_str());
            ImGui::TableSetColumnIndex(4);
            ImGui::Text(table_task.tasks[i].mem_usage.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::EndChild();
}