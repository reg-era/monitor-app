#include "../../include/graphic_ui.h"
using namespace std;

struct SysInfo
{
    string os_name;
    string cmp_name;
    string usr_name;
    string cpu_name;
    int tasks;

    SysInfo()
    {
        os_name = "Linux";
        cmp_name = "Lenovo";
        usr_name = "Regera";
        cpu_name = "i5 Wiw";
        tasks = 3;
    }

    void update_info()
    {
        tasks = tasks + 1;
    }
};

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
    ImGui::Text("Computer name: %s", sys_info.cmp_name.c_str());
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