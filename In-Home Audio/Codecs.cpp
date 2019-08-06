//
//  Codecs.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include "Codecs.hpp"

sf::Packet AudioCodec::Encode(std::vector<sf::Int16> &Samples) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)AudioStreamerPacket::Audio<<(sf::Uint64)Samples.size();
    for(int i=0;i<Samples.size();i++)
        Packet<<Samples[i];
    return Packet;
}
std::vector<sf::Int16> AudioCodec::Decode(sf::Packet &Packet) {
    sf::Uint64 Len;
    Packet>>Len;
    std::vector<sf::Int16> Samples(Len);
    for(int i=0;i<Len;i++)
        Packet>>Samples[i];
    return Samples;
}
