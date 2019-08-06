//
//  Codecs.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Codecs_hpp
#define Codecs_hpp
#include <vector>
#include <SFML/Network.hpp>

enum AudioStreamerPacket {
    Connect=0,
    ConnectAccept=1,
    ConnectReject=2,
    Audio=3,
    Disconnect=4,
    StreamType=5
};

class AudioCodec {
public:
    sf::Packet Encode(std::vector<sf::Int16> &Samples);
    std::vector<sf::Int16> Decode(sf::Packet &Packet);
};

#endif /* Codecs_hpp */
