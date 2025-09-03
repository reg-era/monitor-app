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
    ImGui::Text("Search (PID or name)");
    ImGui::SameLine();

    static char search_buffer[128] = {};
    ImGui::InputText("Search", search_buffer, sizeof(search_buffer));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    if (ImGui::BeginTable("Table Example", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("PID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("State");
        ImGui::TableSetupColumn("CPU usage");
        ImGui::TableSetupColumn("Memory usage");

        ImGui::TableHeadersRow();

        static vector<bool> selected;
        if (selected.size() != table_task.tasks.size())
            selected.resize(table_task.tasks.size(), false);

        for (int i = 0; i < (int)table_task.tasks.size(); i++)
        {
            string keyword = string(search_buffer);
            if (keyword.empty() ||
                table_task.tasks[i].pid.rfind(keyword, 0) == 0 ||
                table_task.tasks[i].name.rfind(keyword, 0) == 0)
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);

                bool is_selected = selected[i];

                if (ImGui::Selectable(table_task.tasks[i].pid.c_str(), is_selected, ImGuiSelectableFlags_SpanAllColumns))
                {
                    if (ImGui::GetIO().KeyCtrl)
                    {
                        selected[i] = !selected[i];
                    }
                    else
                    {
                        fill(selected.begin(), selected.end(), false);
                        selected[i] = true;
                    }
                }

                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(table_task.tasks[i].name.c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::TextUnformatted(table_task.tasks[i].state.c_str());

                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.2f", table_task.tasks[i].cpu_usage);

                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%.2f", table_task.tasks[i].mem_usage);
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
}