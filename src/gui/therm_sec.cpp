#include "../../include/graphic_ui.h"

void DrawThermalSection(float width, float height)
{
    float innerWidth = width * 0.55f;
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::SetCursorPos(ImVec2(width - innerWidth, spacing * 2));
    ImGui::BeginChild("InnerBox", ImVec2(innerWidth - spacing * 2, height - spacing * 4), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Thermal Information");

    static int selectedOption = 0;
    const char *options[] = {"Fan", "Thermal"};
    ImGui::Combo("Select Data", &selectedOption, options, IM_ARRAYSIZE(options));

    static int fps = 50;
    ImGui::SliderInt("FPS", &fps, 0, 100, "fps %d");
    static int yScale = 50;
    ImGui::SliderInt("Scale", &yScale, 0, 100, "scale %d");

    static float values[90] = {};
    static int counter = 0;
    values[counter] = sinf(counter * 0.1f);
    counter = (counter + 1) % 90;
    ImGui::PlotLines("", values, IM_ARRAYSIZE(values), 0, nullptr, -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));

    ImGui::EndChild();
}