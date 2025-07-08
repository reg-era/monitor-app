#include "../../include/graphic_ui.h"

struct ThermalInfo
{
    int option;
    int fps;
    int scale;
    int cpu_count;
    float cpu_diag[90];
    int tem_count;
    float tem_diag[90];
    int fan_count;
    float fan_diag[90];

    ThermalInfo()
    {
        option = 0;
        fps = 50;
        scale = 50;
        cpu_count = 0;
        tem_count = 0;
        fan_count = 0;
    }

    void update_info()
    {
        switch (option)
        {
        case 0:
            cpu_diag[cpu_count] = sinf(cpu_count * 0.1f);
            cpu_count = (cpu_count + 1) % 90;
            break;
        case 1:
            tem_diag[tem_count] = cosf(tem_count * 0.1f);
            tem_count = (tem_count + 1) % 90;
            break;
        case 2:
            fan_diag[fan_count] = tanf(fan_count * 0.1f);
            fan_count = (fan_count + 1) % 90;
            break;
        }
    }
};

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
        thermal_info.update_info();
    }
    ImGui::Checkbox("Animation", &animation);
    const char *options[] = {"cpu", "Fan", "Thermal"};
    ImGui::Combo("Select Data", &thermal_info.option, options, IM_ARRAYSIZE(options));

    ImGui::SliderInt("FPS", &thermal_info.fps, 0, 100, "fps %d");
    ImGui::SliderInt("Scale", &thermal_info.scale, 0, 100, "scale %d");
    ImGui::PopStyleVar();

    switch (thermal_info.option)
    {
    case 0:
        ImGui::PlotLines("cpu", thermal_info.cpu_diag, IM_ARRAYSIZE(thermal_info.cpu_diag), 0, "CPU usage", -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
        break;
    case 1:
        ImGui::PlotLines("thermal", thermal_info.tem_diag, IM_ARRAYSIZE(thermal_info.tem_diag), 0, "Thermal temperature", -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
        break;
    case 2:
        ImGui::PlotLines("fan", thermal_info.fan_diag, IM_ARRAYSIZE(thermal_info.fan_diag), 0, "Fans Rolling", -1.0f, 1.0f, ImVec2(innerWidth - spacing * 6, height / 2));
        break;
    }

    ImGui::EndChild();
}