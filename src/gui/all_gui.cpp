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

void DrawTaskSection(float width, float height)
{
    float spacing = ImGui::GetStyle().ItemSpacing.y;

    ImGui::BeginChild("Middle", ImVec2(width, height), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Task Process Information");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    static char searchText[128] = "";
    ImGui::Text("Search (PID or name)");
    ImGui::SameLine();
    ImGui::InputText("", searchText, IM_ARRAYSIZE(searchText));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    if (ImGui::BeginTable("Table Example", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("PID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("State");
        ImGui::TableSetupColumn("CPU usage");
        ImGui::TableSetupColumn("Memory usage");

        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("2");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("ascii art");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("3");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("kernel");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");

        ImGui::EndTable();
    }
    ImGui::EndChild();
}

void DrawNetworkSection(float width, float height)
{
    ImGui::BeginChild("Footer", ImVec2(width, height * 2), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Network Information");
    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::Text("RX usage:");
    ImGui::SameLine();
    ImGui::Text("0kb");
    ImGui::SameLine();
    ImGui::ProgressBar(0.15, ImVec2(width * 0.35, 20), "15%");
    ImGui::SameLine();
    ImGui::Text("2gb");

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().ItemSpacing.x * 5);
    ImGui::Text("TX usage:");
    ImGui::SameLine();
    ImGui::Text("0kb");
    ImGui::SameLine();
    ImGui::ProgressBar(0.4, ImVec2(width * 0.35, 20), "40%");
    ImGui::SameLine();
    ImGui::Text("2gb");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 4);

    static int selectedOption = 0;
    const char *options[] = {"lo", "wlp0s20f3"};
    ImGui::Combo("Select network interface", &selectedOption, options, IM_ARRAYSIZE(options));

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
    ImGui::Text("IPv4: %s", "10.248.1.134");
    ImGui::Text("IPv6: %s", "fe80::b095:aeef:c50:6930");
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    ImGui::TextColored(ImVec4(200, 0, 0, 1), "RX Tables :");
    // RX: bytes, packets, errs, drop, fifo, frame, compressed and multicast.
    if (ImGui::BeginTable("RX table", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("bytes");
        ImGui::TableSetupColumn("packets");
        ImGui::TableSetupColumn("errs");
        ImGui::TableSetupColumn("drop");
        ImGui::TableSetupColumn("fifo");
        ImGui::TableSetupColumn("frame");
        ImGui::TableSetupColumn("compressed");
        ImGui::TableSetupColumn("multicast");

        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");
        ImGui::TableSetColumnIndex(5);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(6);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(7);
        ImGui::Text("done");

        ImGui::EndTable();
    }

    ImGui::TextColored(ImVec4(200, 0, 0, 1), "TX Tables :");
    // TX: bytes, packets, errs, drop, fifo, colls, carrier and compressed.
    if (ImGui::BeginTable("TX table", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("bytes");
        ImGui::TableSetupColumn("packets");
        ImGui::TableSetupColumn("errs");
        ImGui::TableSetupColumn("drop");
        ImGui::TableSetupColumn("fifo");
        ImGui::TableSetupColumn("colls");
        ImGui::TableSetupColumn("carrier");
        ImGui::TableSetupColumn("compressed");

        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("done");
        ImGui::TableSetColumnIndex(3);
        ImGui::Text("20");
        ImGui::TableSetColumnIndex(4);
        ImGui::Text("10");
        ImGui::TableSetColumnIndex(5);
        ImGui::Text("1");
        ImGui::TableSetColumnIndex(6);
        ImGui::Text("monitor");
        ImGui::TableSetColumnIndex(7);
        ImGui::Text("done");

        ImGui::EndTable();
    }

    ImGui::EndChild();
}
