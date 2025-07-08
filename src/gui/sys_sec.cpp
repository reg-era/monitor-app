#include "../../include/graphic_ui.h"

void DrawHeaderSection(float width, float height)
{
    ImGui::BeginChild("Header", ImVec2(width * 0.6, height), true);
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::TextColored(ImVec4(0, 0, 200, 1), "System Information");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Operating system: %s", "Linux");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Computer name: %s", "HP Elitebook");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("User logged: %s", "REGERA");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("CPU name: %s", "Intel® Core™ i5-10310U 8");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("Working process: %d", 69);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("CPU usage:");

    ImVec2 size = ImVec2(width * 0.6 * 0.4, 20); // width, height

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::ProgressBar(0.75, size, "75%");

    DrawThermalSection(width * 0.6, height);
    ImGui::EndChild();
}