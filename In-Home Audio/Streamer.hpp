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
    Disconnect=4,
    StreamType=5
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
    
    void setBufferSize(sf::Time Size);
protected:
    virtual void onConnectRequest(sf::IpAddress IP);
    virtual void onConnectReject(sf::IpAddress IP);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    virtual void onConnect(sf::IpAddress IP);
    
    void sendSamples(std::vector<sf::Int16> &Samples);
    
    bool m_Connected,m_Listen;
    sf::Time m_BufferSize;
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
    
protected:
    virtual bool onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount);
    virtual void onConnect(sf::IpAddress IP);
};

class SpeakerStreamer : public AudioStreamer, public sf::SoundStream {
public:
    SpeakerStreamer();
    
protected:
    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    bool m_UsingSamples;
    sf::Uint16 m_NumUsed;
    std::vector<sf::Int16> m_Samples;
};

#endif /* Streamer_hpp */
