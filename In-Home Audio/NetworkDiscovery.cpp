//
//  NetworkDiscovery.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

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
            while(m_Search) {
                //Listen
                Status=Socket.receive(Packet,IP,Port);
                if(Status==sf::Socket::Done)
                    std::cout<<"Received from "<<IP<<" on "<<Port<<std::endl;
                else if(Status==sf::Socket::Error)
                    std::cout<<"Socket Error!"<<std::endl;
                //Send
                if(m_Discoverable) {
                    Packet.clear();
                    Packet<<sf::String("Test Name")<<(sf::Uint8)getPlatform();
                    Status=Socket.send(Packet,sf::IpAddress::Broadcast,52575);
                }
                //Wait
                sf::sleep(sf::seconds(.5));
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
