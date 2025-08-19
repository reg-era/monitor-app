#include "../../include/header.h"

#ifndef NET_INFO_H
#define NET_INFO_H

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
        for (auto &[_, net] : iface_map)
        {
            interfaces.push_back(net);
        }
    }
};

#endif