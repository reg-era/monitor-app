#include "../../include/graphic_ui.h"
#include <cstdio>
#include <iostream>
#include <string>

struct MemInfo
{
    float ram_cap;
    float swap_cap;
    float disk_cap;
    float ram_usag;
    float swap_usag;
    float disk_usag;

    MemInfo()
    {
        ram_cap = 16.0;
        swap_cap = 8.0;
        disk_cap = 265.0;
        ram_usag = 0.3;
        swap_usag = 0.1;
        disk_usag = 0.2;
    }

    void update_info()
    {
        ram_usag += 0.001;
        swap_usag += 0.001;
        disk_usag += 0.001;
    }
};

void DrawMemorySection(float width, float height)
{
    static MemInfo mem_info;
    mem_info.update_info();

    ImGui::SameLine();
    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::BeginChild("TopRight", ImVec2(width * 0.4 - spacing * 2, height), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Memmory Information");

    char buffer[20];

    ImGui::Text("Physic Memory (RAM):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    std::snprintf(buffer, sizeof(buffer), "%.2f%%", mem_info.ram_usag * 100);
    ImGui::ProgressBar(mem_info.ram_usag, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 mb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("%.2f gb", mem_info.ram_cap);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Virtual Memory (SWAP):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    std::snprintf(buffer, sizeof(buffer), "%.2f%%", mem_info.swap_usag * 100);
    ImGui::ProgressBar(mem_info.swap_usag, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 mb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("%.2f gb", mem_info.swap_cap);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Disk usage:");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    std::snprintf(buffer, sizeof(buffer), "%.2f%%", mem_info.disk_usag * 100);
    ImGui::ProgressBar(mem_info.disk_usag, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 mb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("%.2f gb", mem_info.disk_cap);

    ImGui::EndChild();
}