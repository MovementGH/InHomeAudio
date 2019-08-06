//
//  NetworkDiscovery.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef NetworkDiscovery_hpp
#define NetworkDiscovery_hpp
#include <vector>
#include <thread>
#include <iostream>
#include <SFML/Network.hpp>
#include "Platform.hpp"
struct NetworkDevice {
    Platform platform;
    sf::String name;
    sf::IpAddress ip;
    sf::Int64 lastSeen;
};

class NetworkDiscovery {
public:
    NetworkDiscovery(bool Discoverable=true);
    ~NetworkDiscovery();
    
    void setDiscoverable(bool Discoverable);
    bool getDiscoverable();
    
    std::vector<NetworkDevice> getDevices();
private:
    std::thread* m_WorkerThread;
    std::vector<NetworkDevice> m_Devices;
    bool m_Discoverable,m_Search;
};

#endif /* NetworkDiscovery_hpp */
