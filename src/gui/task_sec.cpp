#include "../../include/graphic_ui.h"

void DrawTaskSection(float width, float height)
{
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

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("2");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("ascii art");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("3");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("kernel");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::EndTable();
    }
    ImGui::EndChild();
}