#ifndef NetworkDiscovery_hpp
#define NetworkDiscovery_hpp
#include <vector>
#include <thread>
#include <iostream>
#include <SFML/Network.hpp>
#include "Platform.hpp"

class NetworkDiscovery {
public:
    struct Device {
        Platform platform;
        sf::String name;
        sf::IpAddress ip;
        sf::Int64 lastSeen;
    };
    enum PacketType {
        DeviceInfo=0,
        DeviceQuery=1
    };
    
    NetworkDiscovery(bool Discoverable=false);
    ~NetworkDiscovery();
    
    void setDiscoverable(bool Discoverable);
    bool getDiscoverable();
    
    void queryDevice(sf::IpAddress Device);
    
    virtual sf::Packet createPacket();
    virtual Device* decodePacket(sf::Packet& Packet);
    
    
    std::vector<Device*> getDevices();
protected:
    std::thread* m_WorkerThread;
    std::vector<Device*> m_Devices;
    std::vector<sf::IpAddress> m_QueryQueue;
    bool m_Discoverable,m_Search;
};

class StatusDiscovery : public NetworkDiscovery {
public:
    struct Device {
        Platform platform;
        sf::String name;
        sf::IpAddress ip;
        sf::Int64 lastseen;
        sf::String status;
    };
    
    virtual sf::Packet createPacket();
    virtual NetworkDiscovery::Device* decodePacket(sf::Packet& Packet);
    
    void setStatus(sf::String Status);
    
protected:
    sf::String m_Status;
};

#endif /* NetworkDiscovery_hpp */
