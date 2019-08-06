//
//  Devices.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include "Devices.hpp"

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
