#include "../../include/graphic_ui.h"

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
