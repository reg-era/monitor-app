#include "../../include/header.h"
#include "../models/cpu.cpp"

int SectionWindows(int section, CPU *cpu)
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
        ImGui::Text("User: %s", cpu->sysInfo.UserName.c_str());
        ImGui::Text("Host: %s", cpu->sysInfo.HostName.c_str());
        ImGui::Text("CPU Name: %s", cpu->sysInfo.CpuName.c_str());
        ImGui::Text("CPU Type: %s", cpu->sysInfo.CpuType.c_str());

        std::string coresUsage;
        char buffer[64];

        cpu->update(ImGui::GetTime());

        for (int i = 0; i < cpu->getCoreCount(); ++i)
        {
            std::sprintf(buffer, "Core %d: %.2f%%\t", i, cpu->getCoreUsage(i));
            coresUsage += buffer;
        }

        ImGui::TextUnformatted(coresUsage.c_str());
        break;
    }
    case 2:
        ImGui::Text("Displaying Memory information...");
        break;
    case 3:
        ImGui::Text("Displaying Network information...");
        break;
    }

    ImGui::End();
    return 0;
}
