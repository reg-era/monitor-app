#include "../../include/graphic_ui.h"
#include "../../include/models/net_info.h"
#include "../../include/models/mem_info.h"


void DrawNetworkSection(float width, float height)
{
    ImGui::BeginChild("Footer", ImVec2(width, height * 2), true);
    ImGui::TextColored(ImVec4(0, 0, 200, 1), "Network Information");
    float spacing = ImGui::GetStyle().ItemSpacing.y;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);

    static Network net;
    net.update();

    if (ImGui::BeginTabBar("InterfacesTabBar")) // Main interface tab bar
    {
        for (int i = 0; i < (int)net.interfaces.size(); i++)
        {
            if (ImGui::BeginTabItem(net.interfaces[i].name.c_str())) // Begin interface tab
            {
                // RX Usage
                ImGui::Text("RX usage:");
                ImGui::SameLine();
                ImGui::Text("0kb");
                ImGui::SameLine();
                float rx_bytes = float(atoi(net.interfaces[i].reveive.bytes.c_str()));
                float rx_per = rx_bytes / (1024.0f * 1024.0f * 1024.0f);
                ImGui::ProgressBar(rx_per, ImVec2(width * 0.35f, 20), MemInfo::format_size(rx_bytes / 1024.0f).c_str());
                ImGui::SameLine();
                ImGui::Text("2gb");

                // TX Usage
                ImGui::Text("TX usage:");
                ImGui::SameLine();
                ImGui::Text("0kb");
                ImGui::SameLine();
                float tx_bytes = float(atoi(net.interfaces[i].transfer.bytes.c_str()));
                float tx_per = tx_bytes / (1024.0f * 1024.0f * 1024.0f);
                ImGui::ProgressBar(tx_per, ImVec2(width * 0.35f, 20), MemInfo::format_size(tx_bytes / 1024.0f).c_str());
                ImGui::SameLine();
                ImGui::Text("2gb");

                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing * 2);
                ImGui::Text("IPv4: %s", net.interfaces[i].ipv4.c_str());

                // Nested tab bar for RX and TX tables
                if (ImGui::BeginTabBar("PacketsTabBar"))
                {
                    // RX Table
                    if (ImGui::BeginTabItem("RX Tables"))
                    {
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
                            ImGui::Text(net.interfaces[i].reveive.bytes.c_str());
                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text(net.interfaces[i].reveive.packets.c_str());
                            ImGui::TableSetColumnIndex(2);
                            ImGui::Text(net.interfaces[i].reveive.errs.c_str());
                            ImGui::TableSetColumnIndex(3);
                            ImGui::Text(net.interfaces[i].reveive.drop.c_str());
                            ImGui::TableSetColumnIndex(4);
                            ImGui::Text(net.interfaces[i].reveive.fifo.c_str());
                            ImGui::TableSetColumnIndex(5);
                            ImGui::Text(net.interfaces[i].reveive.frame.c_str());
                            ImGui::TableSetColumnIndex(6);
                            ImGui::Text(net.interfaces[i].reveive.compressed.c_str());
                            ImGui::TableSetColumnIndex(7);
                            ImGui::Text(net.interfaces[i].reveive.multicast.c_str());

                            ImGui::EndTable();
                        }
                        ImGui::EndTabItem();
                    }

                    // TX Table
                    if (ImGui::BeginTabItem("TX Tables"))
                    {
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
                            ImGui::Text(net.interfaces[i].transfer.bytes.c_str());
                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text(net.interfaces[i].transfer.packets.c_str());
                            ImGui::TableSetColumnIndex(2);
                            ImGui::Text(net.interfaces[i].transfer.errs.c_str());
                            ImGui::TableSetColumnIndex(3);
                            ImGui::Text(net.interfaces[i].transfer.drop.c_str());
                            ImGui::TableSetColumnIndex(4);
                            ImGui::Text(net.interfaces[i].transfer.fifo.c_str());
                            ImGui::TableSetColumnIndex(5);
                            ImGui::Text(net.interfaces[i].transfer.colls.c_str());
                            ImGui::TableSetColumnIndex(6);
                            ImGui::Text(net.interfaces[i].transfer.carrier.c_str());
                            ImGui::TableSetColumnIndex(7);
                            ImGui::Text(net.interfaces[i].transfer.compressed.c_str());

                            ImGui::EndTable();
                        }
                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar(); // End PacketsTabBar
                }

                ImGui::EndTabItem(); // End interface tab
            }
        }

        ImGui::EndTabBar(); // End InterfacesTabBar
    }

    ImGui::EndChild();
}
