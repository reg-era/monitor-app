#include "../../include/graphic_ui.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unordered_map>

using namespace std;

string format_sec_size(float cap)
{
    const char *units[] = {"KB", "MB", "GB", "TB"};
    int unit_index = 0;

    while (cap >= 1024.0f && unit_index < 3)
    {
        cap /= 1024.0f;
        unit_index++;
    }

    std::ostringstream formatted_size;
    formatted_size << std::fixed << std::setprecision(2) << cap << " " << units[unit_index];

    return formatted_size.str();
}
class NetInter
{
public:
    struct RX
    {
        string bytes;
        string packets;
        string errs;
        string drop;
        string fifo;
        string frame;
        string compressed;
        string multicast;
    };

    struct TX
    {
        string bytes;
        string packets;
        string errs;
        string drop;
        string fifo;
        string colls;
        string carrier;
        string compressed;
    };

    string name;
    string ipv4;
    RX reveive;
    TX transfer;
};

struct Network
{
    vector<NetInter> interfaces;

    void update()
    {
        interfaces.clear();
        unordered_map<string, NetInter> iface_map;

        // 1. Read /proc/net/dev for RX/TX stats
        ifstream dev("/proc/net/dev");
        string line;
        // Skip the first 2 header lines
        getline(dev, line);
        getline(dev, line);

        while (getline(dev, line))
        {
            istringstream ss(line);
            string iface;
            getline(ss, iface, ':'); // Get the interface name

            // Trim whitespace
            iface.erase(0, iface.find_first_not_of(" \t"));
            iface.erase(iface.find_last_not_of(" \t") + 1);

            NetInter net;
            net.name = iface;

            // Read RX and TX stats
            ss >> net.reveive.bytes >> net.reveive.packets >> net.reveive.errs >> net.reveive.drop >> net.reveive.fifo >> net.reveive.frame >> net.reveive.compressed >> net.reveive.multicast >> net.transfer.bytes >> net.transfer.packets >> net.transfer.errs >> net.transfer.drop >> net.transfer.fifo >> net.transfer.colls >> net.transfer.carrier >> net.transfer.compressed;

            iface_map[iface] = net;
        }

        // 2. Get IPv4 using getifaddrs
        struct ifaddrs *ifaddr;
        if (getifaddrs(&ifaddr) == 0)
        {
            for (struct ifaddrs *ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
            {
                if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET)
                    continue;

                string name = ifa->ifa_name;
                char ip[INET_ADDRSTRLEN];
                void *addr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;

                inet_ntop(AF_INET, addr, ip, INET_ADDRSTRLEN);

                if (iface_map.count(name))
                {
                    iface_map[name].ipv4 = ip;
                }
            }
            freeifaddrs(ifaddr);
        }

        // 3. Move to vector
        for (auto &[name, net] : iface_map)
        {
            interfaces.push_back(net);
        }
    }
};

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
                ImGui::ProgressBar(rx_per, ImVec2(width * 0.35f, 20), format_sec_size(rx_bytes / 1024.0f).c_str());
                ImGui::SameLine();
                ImGui::Text("2gb");

                // TX Usage
                ImGui::Text("TX usage:");
                ImGui::SameLine();
                ImGui::Text("0kb");
                ImGui::SameLine();
                float tx_bytes = float(atoi(net.interfaces[i].transfer.bytes.c_str()));
                float tx_per = tx_bytes / (1024.0f * 1024.0f * 1024.0f);
                ImGui::ProgressBar(tx_per, ImVec2(width * 0.35f, 20), format_sec_size(tx_bytes / 1024.0f).c_str());
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
