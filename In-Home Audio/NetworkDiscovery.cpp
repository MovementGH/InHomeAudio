#include "NetworkDiscovery.hpp"

NetworkDiscovery::NetworkDiscovery(bool Discoverable) : m_Discoverable(Discoverable), m_Search(true) {
    m_WorkerThread=new std::thread([&]{
        sf::UdpSocket Socket;
        Socket.setBlocking(true);
        sf::Socket::Status Status=Socket.bind(52575);
        Socket.setBlocking(false);
        if(Status==sf::Socket::Done) {
            sf::Packet Packet;
            sf::IpAddress IP;
            sf::Uint16 Port;
            time_t Time;
            while(m_Search) {
                //Listen
                Status=sf::Socket::Done;
                while(Status==sf::Socket::Done) {
                    Status=Socket.receive(Packet,IP,Port);
                    if(Status==sf::Socket::Done&&IP!=sf::IpAddress::getLocalAddress()) {
                        sf::String name;
                        sf::Uint8 platform;
                        std::time(&Time);
                        Packet>>name>>platform;
                        bool Found=false;
                        for(int i=0;i<m_Devices.size()&&Found==false;i++) {
                            if(m_Devices[i].ip==IP) {
                                m_Devices[i].lastSeen=Time;
                                m_Devices[i].name=name;
                                m_Devices[i].platform=(Platform)platform;
                                Found=true;
                            }
                        }
                        if(Found==false) {
                            NetworkDevice NewDevice;
                            NewDevice.ip=IP;
                            NewDevice.lastSeen=Time;
                            NewDevice.name=name;
                            NewDevice.platform=(Platform)platform;
                            m_Devices.push_back(NewDevice);
                        }
                    }
                    else if(Status==sf::Socket::Error)
                        std::cout<<"Socket Error!"<<std::endl;
                }
                //Send
                if(m_Discoverable) {
                    Packet.clear();
                    Packet<<(sf::String)getComputerName()<<(sf::Uint8)getPlatform();
                    Status=Socket.send(Packet,sf::IpAddress::Broadcast,52575);
                }
                //Wait
                sf::sleep(sf::seconds(1));
            }
        }
        else
            std::cout<<"Failed to bind!"<<std::endl;
    });
}
NetworkDiscovery::~NetworkDiscovery() {
    m_Search=false;
    m_WorkerThread->join();
    delete m_WorkerThread;
}

void NetworkDiscovery::setDiscoverable(bool Discoverable) {
    m_Discoverable=Discoverable;
}
bool NetworkDiscovery::getDiscoverable() {
    return m_Discoverable;
}

std::vector<NetworkDevice> NetworkDiscovery::getDevices() {
    return m_Devices;
}
