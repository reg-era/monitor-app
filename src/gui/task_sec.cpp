#include "../../include/header.h"
#include "../../include/models/task_info.h"

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