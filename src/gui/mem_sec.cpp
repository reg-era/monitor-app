#include "../../include/graphic_ui.h"

void DrawMemorySection(float width, float height)
{
    ImGui::SameLine();

    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::BeginChild("TopRight", ImVec2(width * 0.4 - spacing * 2, height), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Memmory Information");

    ImGui::Text("Physic Memory (RAM):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::ProgressBar(0.2, ImVec2(width * 0.35, 20), "20%");
    ImGui::Text("0kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("16gb");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Virtual Memory (SWAP):");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::ProgressBar(0.15, ImVec2(width * 0.35, 20), "15%");
    ImGui::Text("0kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("8gb");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("Disk usage:");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::ProgressBar(0.4, ImVec2(width * 0.35, 20), "40%");
    ImGui::Text("0kb");
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + width * 0.3);
    ImGui::Text("256gb");

    ImGui::EndChild();
}