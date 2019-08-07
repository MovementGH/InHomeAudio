#include <iostream>
#include "NetworkDiscovery.hpp"
#include "Devices.hpp"

int main(int argc, const char * argv[]) {
    
    
    
    DualDeviceStreamerStreamer Streamer;
    Streamer.setCodec<OpusCodec>(new OpusCodec(32000));
    Streamer.Connect("192.168.1.143");
    Streamer.setBufferSize(sf::seconds(.2));
    sf::sleep(sf::seconds(60));
//    while(true) {
//        std::vector<NetworkDevice> Devices=Discoverer.getDevices();
//        for(int i=0;i<Devices.size();i++)
//            std::cout<<(std::string)Devices[i].name<<" from "<<Devices[i].ip<<" on "<<getPlatformName(Devices[i].platform)<<" at "<<Devices[i].lastSeen<<std::endl;
//        std::cout<<std::endl<<std::endl;
//        sf::sleep(sf::seconds(1));
//    }
    
}
