//
//  main.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include <iostream>
#include "NetworkDiscovery.hpp"
#include "Devices.hpp"

int main(int argc, const char * argv[]) {
    NetworkDiscovery Discoverer(true);
    
    
    
    InputDeviceStreamer Streamer;
    Streamer.setCodec<OpusCodec>();
    Streamer.Connect("192.168.1.143");
//    Streamer.setBufferSize(sf::seconds(0.2));
    sf::sleep(sf::seconds(10));
//    while(true) {
//        std::vector<NetworkDevice> Devices=Discoverer.getDevices();
//        for(int i=0;i<Devices.size();i++)
//            std::cout<<(std::string)Devices[i].name<<" from "<<Devices[i].ip<<" on "<<getPlatformName(Devices[i].platform)<<" at "<<Devices[i].lastSeen<<std::endl;
//        std::cout<<std::endl<<std::endl;
//        sf::sleep(sf::seconds(1));
//    }
    
}
