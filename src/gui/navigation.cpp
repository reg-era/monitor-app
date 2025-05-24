#include "../../include/header.h"

int HeaderNavigation(ImVec2 size)
{
    float navHeight = size.y * 0.05f;
    float buttonWidth = size.x / 3.0f;
    ImVec2 buttonSize(buttonWidth, navHeight);

    static int currentTab = 1;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(size.x, navHeight));

    // Optional style tweak: remove inner padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    // Begin nav bar window
    ImGui::Begin("Navigation", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoScrollWithMouse);

    if (ImGui::Button("CPU", buttonSize))
        currentTab = 1;

    ImGui::SameLine();
    if (ImGui::Button("Memory", buttonSize))
        currentTab = 2;

    ImGui::SameLine();
    if (ImGui::Button("Network", buttonSize))
        currentTab = 3;

    ImGui::End();
    ImGui::PopStyleVar();

    return currentTab;
}
