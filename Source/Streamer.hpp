#ifndef Streamer_hpp
#define Streamer_hpp
#include <iostream>
#include <thread>
#include "Platform.hpp"
#include "Codecs.hpp"
#include "Filters.hpp"

#define StreamerPort 18500

class AudioStreamer {
public:
    enum Payload {
        Audio=0,
        Connect=1,
        ConnectAccept=1,
        ConnectReject=2,
        Disconnect=4,
        StreamMeta=5
    };
    
    AudioStreamer();
    ~AudioStreamer();
    
    void connect(sf::IpAddress IP);
    void disconnect();
    
    bool isConnected();
    
    template<typename CodecType>void setCodec(CodecType* Codec=new CodecType()){m_Codec=Codec;}
    
    void setBufferSize(sf::Time Size);
protected:
    virtual void onConnectRequest(sf::IpAddress IP);
    virtual void onConnectReject(sf::IpAddress IP);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onPacket(sf::Uint8 Type,sf::Packet& Packet);
    virtual void onMeta(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    virtual void onConnect(sf::IpAddress IP);
    virtual void onDisconnect();
    
    void sendSamples(std::vector<sf::Int16> &Samples);
    void sendMeta(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    
    bool m_Connected,m_Listen;
    sf::Time m_BufferSize;
    std::thread* m_WorkerThread;
    sf::UdpSocket m_SocketOut,m_SocketIn;
    sf::IpAddress m_IP;
    std::vector<AudioFilter*> m_FilterIn,m_FilterOut;
    AudioCodec* m_Codec;
};

#endif /* Streamer_hpp */
