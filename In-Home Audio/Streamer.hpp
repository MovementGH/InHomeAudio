//
//  Streamer.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Streamer_hpp
#define Streamer_hpp
#include <iostream>
#include <vector>
#include <thread>
#include <SFML/Network.hpp>
#include "Platform.hpp"
enum AudioStreamerPacket {
    Connect=0,
    ConnectAccept=1,
    ConnectReject=2,
    Audio=3
};


class AudioCodec {
public:
    sf::Packet Encode(std::vector<sf::Int32> &Samples);
    std::vector<sf::Int32> Decode(sf::Packet &Packet);
};
class AudioFilter {
public:
    bool Filter(std::vector<sf::Int32>& Samples);
};
class AudioStreamer {
public:
    AudioStreamer();
    ~AudioStreamer();
    
    void Connect(sf::IpAddress IP);
    void Disconnect();
    
    bool isConnected();
    
    void sendSamples(std::vector<sf::Int32> &Samples);
protected:
    virtual void onConnectRequest(sf::IpAddress IP);
    virtual void onConnectReject(sf::IpAddress IP);
    virtual void onSamples(std::vector<sf::Int32> &Samples);
    
    bool m_Connected,m_Listen;
    std::thread* m_WorkerThread;
    sf::UdpSocket m_SocketOut,m_SocketIn;
    sf::IpAddress m_IP;
    std::vector<AudioFilter*> m_FilterIn,m_FilterOut;
    AudioCodec* m_Codec;
};

#endif /* Streamer_hpp */
