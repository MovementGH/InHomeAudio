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
#include <SFML/Audio.hpp>
#include "Platform.hpp"
enum AudioStreamerPacket {
    Connect=0,
    ConnectAccept=1,
    ConnectReject=2,
    Audio=3,
    Disconnect=4
};


class AudioCodec {
public:
    sf::Packet Encode(std::vector<sf::Int16> &Samples);
    std::vector<sf::Int16> Decode(sf::Packet &Packet);
};
class AudioFilter {
public:
    bool Filter(std::vector<sf::Int16>& Samples);
};
class AudioStreamer {
public:
    AudioStreamer();
    ~AudioStreamer();
    
    void Connect(sf::IpAddress IP);
    void Disconnect();
    
    bool isConnected();
    
protected:
    virtual void onConnectRequest(sf::IpAddress IP);
    virtual void onConnectReject(sf::IpAddress IP);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    
    void sendSamples(std::vector<sf::Int16> &Samples);
    
    bool m_Connected,m_Listen;
    std::thread* m_WorkerThread;
    sf::UdpSocket m_SocketOut,m_SocketIn;
    sf::IpAddress m_IP;
    std::vector<AudioFilter*> m_FilterIn,m_FilterOut;
    AudioCodec* m_Codec;
};

//Extras

class MicStreamer : public AudioStreamer, public sf::SoundBufferRecorder {
public:
    MicStreamer();
    void Play();
    void Pause();
    
protected:
    virtual bool onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount);
};

#endif /* Streamer_hpp */
