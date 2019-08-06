//
//  Streamer.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include "Streamer.hpp"

AudioStreamer::AudioStreamer() : m_Connected(false),m_Listen(true),m_BufferSize(sf::seconds(.1)) {
    m_Codec=new AudioCodec();
    m_SocketOut.setBlocking(false);
    m_SocketIn.setBlocking(true);
    sf::Socket::Status Status=m_SocketIn.bind(18500);
    m_SocketIn.setBlocking(false);
    if(Status==sf::Socket::Done) {
        m_WorkerThread=new std::thread([&]{
            sf::Socket::Status Status;
            sf::IpAddress IP;
            sf::Uint16 Port;
            while(m_Listen) {
                Status=sf::Socket::Done;
                while(Status==sf::Socket::Done) {
                    sf::Packet Packet;
                    Status=m_SocketIn.receive(Packet,IP,Port);
                    if(Status==sf::Socket::Done) {
                        sf::Uint8 Type;
                        Packet>>Type;
                        if(Type==AudioStreamerPacket::Connect)
                            onConnectRequest(IP);
                        else if(Type==AudioStreamerPacket::ConnectAccept) {
                            m_Connected=true;
                            m_IP=IP;
                            onConnect(IP);
                        }
                        else if(Type==AudioStreamerPacket::ConnectReject)
                            onConnectReject(IP);
                        else if(Type==AudioStreamerPacket::Audio) {
                            std::vector<sf::Int16> Samples=m_Codec->Decode(Packet);
                            bool UseSamples=true;
                            for(int i=0;i<m_FilterIn.size();i++)
                                if(m_FilterIn[i]->Filter(Samples)==false)
                                    UseSamples=false;
                            if(UseSamples)
                                onSamples(Samples);
                        }
                        else if(Type==AudioStreamerPacket::Disconnect)
                            m_Connected=false;
                        else if(Type==AudioStreamerPacket::StreamType) {
                            sf::Uint8 ChannelCount;
                            sf::Uint32 SampleRate;
                            Packet>>ChannelCount>>SampleRate;
                            onGetStats(ChannelCount,SampleRate);
                        }
                    }
                    else if(Status==sf::Socket::Error)
                        std::cout<<"Socket Error"<<std::endl;
                }
                sf::sleep(sf::milliseconds(1));
            }
        });
    }
    else if(Status==sf::Socket::Error)
        std::cout<<"Binding Error"<<std::endl;
}
AudioStreamer::~AudioStreamer() {
    Disconnect();
    m_Listen=false;
    m_WorkerThread->join();
}
void AudioStreamer::Connect(sf::IpAddress IP) {
    if(m_Connected==false) {
        sf::Packet Packet;
        Packet<<(sf::Uint8)AudioStreamerPacket::Connect;
        m_SocketOut.setBlocking(true);
        m_SocketOut.send(Packet,IP,18500);
        m_SocketOut.setBlocking(false);
    }
}
void AudioStreamer::Disconnect() {
    if(m_Connected) {
        sf::Packet Packet;
        Packet<<(sf::Uint8)AudioStreamerPacket::Disconnect;
        m_SocketOut.setBlocking(true);
        m_SocketOut.send(Packet,m_IP,18500);
        m_SocketOut.setBlocking(false);
        m_Connected=false;
    }
}
bool AudioStreamer::isConnected() {
    return m_Connected;
}
void AudioStreamer::sendSamples(std::vector<sf::Int16> &Samples) {
    if(m_Connected) {
        for(int i=0;i<m_FilterOut.size();i++)
            if(m_FilterOut[i]->Filter(Samples)==false)
                return;
        sf::Packet Packet=m_Codec->Encode(Samples);
        m_SocketOut.send(Packet,m_IP,18500);
    }
}
void AudioStreamer::setBufferSize(sf::Time Size) {
    m_BufferSize=Size;
}
void AudioStreamer::onSamples(std::vector<sf::Int16> &Samples){}
void AudioStreamer::onConnectReject(sf::IpAddress IP){}
void AudioStreamer::onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate){}
void AudioStreamer::onConnect(sf::IpAddress IP){}
void AudioStreamer::onConnectRequest(sf::IpAddress IP) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)AudioStreamerPacket::ConnectAccept;
    m_SocketOut.send(Packet,IP,18500);
    m_IP=IP;
    m_Connected=true;
    onConnect(IP);
}


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
bool AudioFilter::Filter(std::vector<sf::Int16> &Samples) {
    return true;
}


MicStreamer::MicStreamer() {
    setChannelCount(2);
    setProcessingInterval(sf::milliseconds(25));
}
void MicStreamer::onConnect(sf::IpAddress IP) {
    start();
    sf::Packet Packet;
    Packet<<(sf::Uint8)AudioStreamerPacket::StreamType<<(sf::Uint8)2<<(sf::Uint32)getSampleRate();
    m_SocketOut.send(Packet,IP,18500);
}
bool MicStreamer::onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount) {
    if(SampleCount>40000) return true;
    std::vector<sf::Int16> SampleVec(SampleCount);
    for(int i=0;i<SampleCount;i++)
        SampleVec[i]=Samples[i];
    sendSamples(SampleVec);
    return true;
}

SpeakerStreamer::SpeakerStreamer() : m_NumUsed(0) {
    
}
void SpeakerStreamer::onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate) {
    
    initialize(ChannelCount,SampleRate);
    play();
}
bool SpeakerStreamer::onGetData(Chunk& data) {
    while(m_UsingSamples==true) { sf::sleep(sf::milliseconds(1)); }
    m_Samples.erase(m_Samples.begin(),m_Samples.begin()+m_NumUsed);
    if(m_Samples.size()>=4096) {
        m_UsingSamples=false;
        data.samples=m_Samples.data();
        data.sampleCount=4096;
        m_NumUsed=4096;
    }
    else {
        m_Samples.insert(m_Samples.begin(),1024,0);
        m_UsingSamples=false;
        data.samples=m_Samples.data();
        data.sampleCount=1024;
        m_NumUsed=1024;
    }
    return true;
}
void SpeakerStreamer::onSeek(sf::Time timeOffset) {
    
}
void SpeakerStreamer::onSamples(std::vector<sf::Int16>& Samples) {
    while(m_UsingSamples==true) { sf::sleep(sf::milliseconds(1)); }
    m_UsingSamples=true;
    m_Samples.insert(m_Samples.end(),Samples.begin(),Samples.end());
    if(m_Samples.size()>(getSampleRate()*getChannelCount())*m_BufferSize.asSeconds()) m_Samples.erase(m_Samples.begin(),m_Samples.end()-((getSampleRate()*getChannelCount())*m_BufferSize.asSeconds()));
    m_UsingSamples=false;
}
