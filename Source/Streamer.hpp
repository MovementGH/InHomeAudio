#ifndef Streamer_hpp
#define Streamer_hpp
#include <iostream>
#include <thread>
#include "Platform.hpp"
#include "Codecs.hpp"
#include "Filters.hpp"

class AudioStreamer {
public:
    AudioStreamer();
    ~AudioStreamer();
    
    void Connect(sf::IpAddress IP);
    void Disconnect();
    
    bool isConnected();
    
    template<typename CodecType>void setCodec(CodecType* Codec=new CodecType()){m_Codec=Codec;}
    
    void setBufferSize(sf::Time Size);
protected:
    virtual void onConnectRequest(sf::IpAddress IP);
    virtual void onConnectReject(sf::IpAddress IP);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    virtual void onConnect(sf::IpAddress IP);
    virtual void onDisconnect();
    
    void sendSamples(std::vector<sf::Int16> &Samples);
    
    bool m_Connected,m_Listen;
    sf::Time m_BufferSize;
    std::thread* m_WorkerThread;
    sf::UdpSocket m_SocketOut,m_SocketIn;
    sf::IpAddress m_IP;
    std::vector<AudioFilter*> m_FilterIn,m_FilterOut;
    AudioCodec* m_Codec;
};

#endif /* Streamer_hpp */
