#include "../../include/prepare.h"

int SectionWindows(int section, CPU cpu, Memory mem)
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    float navHeight = windowSize.y * 0.05f;
    float margin = (windowSize.y + windowSize.x) * 0.01f;
    ImVec2 sectionPos(0 + margin, navHeight + margin);
    ImVec2 sectionSize(windowSize.x - margin * 2, windowSize.y - navHeight - margin * 2);

    ImGui::SetNextWindowPos(sectionPos);
    ImGui::SetNextWindowSize(sectionSize);

    ImGui::Begin("Section", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    switch (section)
    {
    case 1:
    {
        ImGui::Text("User: %s", cpu.sysInfo.UserName.c_str());
        ImGui::Text("Host: %s", cpu.sysInfo.HostName.c_str());
        ImGui::Text("CPU Name: %s", cpu.sysInfo.CpuName.c_str());
        ImGui::Text("CPU Type: %s", cpu.sysInfo.CpuType.c_str());

        std::string coresUsage;
        char buffer[64];

        cpu.update(ImGui::GetTime());

        for (int i = 0; i < cpu.getCoreCount(); ++i)
        {
            std::sprintf(buffer, "Core %d: %.2f%%\t", i, cpu.getCoreUsage(i));
            coresUsage += buffer;
        }

        ImGui::TextUnformatted(coresUsage.c_str());
        break;
    }
    case 2:
        ImGui::Text("Displaying Memory information...");

        ImGui::Text("RAM Usage: %.2f GB / %.2f GB", mem.usedRAM / 1024.0 / 1024.0, mem.totalRAM / 1024.0 / 1024.0);
        ImGui::ProgressBar((float)mem.usedRAM / mem.totalRAM, ImVec2(-1, 0));

        ImGui::Text("Swap Usage: %.2f GB / %.2f GB", mem.usedSwap / 1024.0 / 1024.0, mem.totalSwap / 1024.0 / 1024.0);
        ImGui::ProgressBar(mem.totalSwap > 0 ? (float)mem.usedSwap / mem.totalSwap : 0.f, ImVec2(-1, 0));

        ImGui::Text("Disk Usage (on wiiiw): %.2f GB / %.2f GB", mem.usedDisk / 1024.0 / 1024.0 / 1024.0, mem.totalDisk / 1024.0 / 1024.0 / 1024.0);
        ImGui::ProgressBar(mem.totalDisk > 0 ? (float)mem.usedDisk / mem.totalDisk : 0.f, ImVec2(-1, 0));
        break;
    case 3:
        ImGui::Text("Displaying Network information...");
        break;
    }

    ImGui::End();
    return 0;
}
