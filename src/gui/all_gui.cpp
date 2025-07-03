#include "../../include/graphic_ui.h"

void DrawHeaderSection(float width, float height)
{
    ImGui::BeginChild("TopLeft", ImVec2(width * 0.6, height), true);

    DrawThermalSection(width * 0.6, height);

    ImGui::EndChild();
}

void DrawThermalSection(float width, float height)
{
    float innerWidth = width * 0.5f;
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::SetCursorPos(ImVec2(width - innerWidth, spacing * 2));
    ImGui::BeginChild("InnerBox", ImVec2(innerWidth - spacing * 2, height - spacing * 4), true);
    ImGui::Text("Inner Box");
    ImGui::EndChild();
}

void DrawMemorySection(float width, float height)
{
    ImGui::SameLine();

    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::BeginChild("TopRight", ImVec2(width * 0.4 - spacing * 2, height), true);
    ImGui::Text("Top Right");
    ImGui::EndChild(); // End TopRight
}

void DrawTaskSection(float width, float height)
{
    ImGui::BeginChild("Middle", ImVec2(width, height), true);
    ImGui::Text("Middle Section");
    ImGui::EndChild();
}

void DrawNetworkSection(float width, float height)
{
    ImGui::BeginChild("Footer", ImVec2(width, height * 2), true);
    ImGui::Text("Footer Section");
    ImGui::EndChild();
}
