//
//  Streamer.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include "Streamer.hpp"

AudioStreamer::AudioStreamer() : m_Connected(false),m_Listen(true) {
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
                    }
                    else if(Type==AudioStreamerPacket::ConnectReject)
                        onConnectReject(IP);
                    else if(Type==AudioStreamerPacket::Audio) {
                        std::vector<sf::Int32> Samples;
                        m_Codec->Decode(Packet);
                        bool UseSamples=true;
                        for(int i=0;i<m_FilterIn.size();i++)
                            if(m_FilterIn[i]->Filter(Samples)==false)
                                UseSamples=false;
                        if(UseSamples)
                            onSamples(Samples);
                    }
                }
                else if(Status==sf::Socket::Error)
                    std::cout<<"Socket Error"<<std::endl;
            }
        });
    }
    else if(Status==sf::Socket::Error)
        std::cout<<"Binding Error"<<std::endl;
}
AudioStreamer::~AudioStreamer() {
    m_Connected=false;
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
    m_Connected=false;
}
bool AudioStreamer::isConnected() {
    return m_Connected;
}
void AudioStreamer::sendSamples(std::vector<sf::Int32> &Samples) {
    if(m_Connected) {
        for(int i=0;i<m_FilterOut.size();i++)
            if(m_FilterOut[i]->Filter(Samples)==false)
                return;
        sf::Packet Packet=m_Codec->Encode(Samples);
        m_SocketOut.send(Packet,m_IP,18500);
    }
}

void AudioStreamer::onSamples(std::vector<sf::Int32> &Samples) {
    std::cout<<"Received "<<Samples.size()<<" samples"<<std::endl;
}
void AudioStreamer::onConnectReject(sf::IpAddress IP) {
    
}
void AudioStreamer::onConnectRequest(sf::IpAddress IP) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)AudioStreamerPacket::ConnectAccept;
    m_SocketOut.send(Packet,IP,18500);
}

sf::Packet AudioCodec::Encode(std::vector<sf::Int32> &Samples) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)AudioStreamerPacket::Audio<<(sf::Uint64)Samples.size();
    for(int i=0;i<Samples.size();i++)
        Packet<<Samples[i];
    return Packet;
}
std::vector<sf::Int32> AudioCodec::Decode(sf::Packet &Packet) {
    sf::Uint64 Len;
    Packet>>Len;
    std::vector<sf::Int32> Samples(Len);
    for(int i=0;i<Len;i++)
        Packet>>Samples[i];
    return Samples;
}
bool AudioFilter::Filter(std::vector<sf::Int32> &Samples) {
    return true;
}
