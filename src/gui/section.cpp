#include "../../include/header.h"

int SectionWindows(int section)
{
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    float navHeight = windowSize.y * 0.05f;
    float margin = (windowSize.y + windowSize.x) * 0.01f;
    ImVec2 sectionPos(0 + margin, navHeight + margin);
    ImVec2 sectionSize(windowSize.x - margin*2, windowSize.y - navHeight - margin*2);

    ImGui::SetNextWindowPos(sectionPos);
    ImGui::SetNextWindowSize(sectionSize);

    ImGui::Begin("Section", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse);

    switch (section)
    {
    case 1:
        ImGui::Text("Displaying CPU information...");
        break;
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
