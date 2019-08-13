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
            int Loops=0;
            while(m_Search) {
                if(Loops%20==0) {
                    Status=sf::Socket::Done;
                    while(Status==sf::Socket::Done) {
                        Status=Socket.receive(Packet,IP,Port);
                        if(Status==sf::Socket::Done&&IP!=sf::IpAddress::getLocalAddress()) {
                            Device* Received=decodePacket(Packet);
                            Received->ip=IP;
                            bool Found=false;
                            for(int i=0;i<m_Devices.size()&&Found==false;i++)
                                if(m_Devices[i]->ip==IP)
                                    delete m_Devices[i],
                                    m_Devices[i]=Received,
                                    Found=true;
                            if(Found==false) m_Devices.push_back(Received);
                        }
                        else if(Status==sf::Socket::Error)
                            std::cout<<"Socket Error!"<<std::endl;
                    }
                    if(m_Discoverable) {
                        Packet=createPacket();
                        Socket.send(Packet,sf::IpAddress::Broadcast,52575);
                    }
                    
                }
                sf::sleep(sf::seconds(.1));
            }
        }
        else
            std::cout<<"Failed to bind!"<<std::endl;
    });
}
NetworkDiscovery::Device* NetworkDiscovery::decodePacket(sf::Packet& Packet) {
    sf::String Name;
    sf::Uint8 platform;
    time_t Time;
    std::time(&Time);
    Packet>>Name>>platform;
    Device* Received=new Device();
    Received->lastSeen=Time;
    Received->name=Name;
    Received->platform=(Platform)platform;
    return Received;
}
sf::Packet NetworkDiscovery::createPacket() {
    sf::Packet Packet;
    Packet<<(sf::String)getComputerName()<<(sf::Uint8)getPlatform();
    return Packet;
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
std::vector<NetworkDiscovery::Device*> NetworkDiscovery::getDevices() {
    return m_Devices;
}


NetworkDiscovery::Device* StatusDiscovery::decodePacket(sf::Packet& Packet) {
    sf::String Name,Status;
    sf::Uint8 platform;
    time_t Time;
    std::time(&Time);
    Packet>>Name>>platform>>Status;
    Device* Received=new Device();
    Received->lastseen=Time;
    Received->name=Name;
    Received->platform=(Platform)platform;
    Received->status=Status;
    return (NetworkDiscovery::Device*)Received;
}
sf::Packet StatusDiscovery::createPacket() {
    sf::Packet Packet;
    Packet<<(sf::String)getComputerName()<<(sf::Uint8)getPlatform()<<m_Status;
    return Packet;
}
void StatusDiscovery::setStatus(sf::String Status){m_Status=Status;}
