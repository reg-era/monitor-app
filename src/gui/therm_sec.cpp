#include "../../include/header.h"
#include "../../include/models/therm_info.h"

void DrawThermalSection(float width, float height)
{
    static ThermalInfo thermal_info;

    float innerWidth = width * 0.55f;
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::SetCursorPos(ImVec2(width - innerWidth, spacing * 2));
    ImGui::BeginChild("InnerBox", ImVec2(innerWidth - spacing * 2, height - spacing * 4), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Thermal Information");
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.5, 0.5));

    static bool animation = true;
    if (animation)
    {
        float delta_time = ImGui::GetIO().DeltaTime;
        thermal_info.update_info(delta_time);
    }
    ImGui::Checkbox("Animation", &animation);
    ImGui::SliderInt("FPS", &thermal_info.fps, 0, 100, "fps %d");
    ImGui::SliderInt("Scale", &thermal_info.scale, 0, 100, "scale %d");

    if (ImGui::BeginTabBar("ThermalTabs"))
    {
        if (ImGui::BeginTabItem("CPU"))
        {
            thermal_info.option = 0;
            ImGui::PlotLines("", thermal_info.cpu_diag, IM_ARRAYSIZE(thermal_info.cpu_diag), 0, "CPU usage", 0.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Thermal"))
        {
            thermal_info.option = 1;
            ImGui::PlotLines("", thermal_info.tem_diag, IM_ARRAYSIZE(thermal_info.tem_diag), 0, "Thermal temperature", -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Fan"))
        {
            thermal_info.option = 2;
            ImGui::PlotLines("", thermal_info.fan_diag, IM_ARRAYSIZE(thermal_info.fan_diag), 0, "Fan Speed", -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::PopStyleVar();
    ImGui::EndChild();
}
