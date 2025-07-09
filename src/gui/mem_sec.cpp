#include "../../include/header.h"
#include "../../include/models/mem_info.h"

string format_size(float cap)
{
    const char *units[] = {"KB", "MB", "GB", "TB"};
    int unit_index = 0;

    while (cap >= 1024.0f && unit_index < 3)
    {
        cap /= 1024.0f;
        unit_index++;
    }

    std::ostringstream formatted_size;
    formatted_size << std::fixed << std::setprecision(2) << cap << " " << units[unit_index];

    return formatted_size.str();
}

void DrawMemorySection(float width, float height)
{
    static MemInfo mem_info = MemInfo();
    mem_info.update_info();

    ImGui::SameLine();
    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::BeginChild("TopRight", ImVec2(width * 0.4 - spacing * 2, height), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Memmory Information");

    char buffer[20];

    ImGui::Text("Physic Memory (RAM):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    float ram_used = float(mem_info.mem_total - mem_info.mem_free - mem_info.mem_buffr - mem_info.mem_cach);
    float percent_ram = (ram_used / mem_info.mem_total);
    std::snprintf(buffer, sizeof(buffer), "%.2f%% %s", percent_ram * 100, format_size(ram_used).c_str());
    ImGui::ProgressBar(percent_ram, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text(format_size(float(mem_info.mem_total)).c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Virtual Memory (SWAP):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    float percent_swap = (float(mem_info.swap_usag) / mem_info.swap_cap) * 100;
    std::snprintf(buffer, sizeof(buffer), "%.2f%% %s", percent_swap * 100, format_size(float(mem_info.swap_usag)).c_str());
    ImGui::ProgressBar(percent_swap, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text(format_size(float(mem_info.swap_cap)).c_str());
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Disk usage:");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    float percent_disk = (float(mem_info.disk_usag) / mem_info.disk_cap);
    std::snprintf(buffer, sizeof(buffer), "%.2f%% %s", percent_disk * 100, format_size(float(mem_info.disk_usag)).c_str());
    ImGui::ProgressBar(percent_disk, ImVec2(width * 0.35, 20), buffer);
    ImGui::Text("0 kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text(format_size(float(mem_info.disk_cap)).c_str());

    ImGui::EndChild();
}