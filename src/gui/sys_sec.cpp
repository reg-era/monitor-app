#include "../../include/header.h"
#include "../../include/graphic_ui.h"
#include "../../include/models/sys_info.h"


void DrawHeaderSection(float width, float height)
{
    static SysInfo sys_info;
    sys_info.update_info();

    ImGui::BeginChild("Header", ImVec2(width * 0.6, height), true);
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::TextColored(ImVec4(0, 0, 200, 1), "System Information");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Operating system: %s", sys_info.os_name.c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Host name: %s", sys_info.host_name.c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("User logged: %s", sys_info.usr_name.c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("CPU name: %s", sys_info.cpu_name.c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Working process: %d", sys_info.tasks);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    DrawThermalSection(width * 0.6, height);
    ImGui::EndChild();
}