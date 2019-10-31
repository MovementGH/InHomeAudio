#include "Devices.hpp"

InputDeviceStreamer::InputDeviceStreamer() {
    setChannelCount(2);
    setProcessingInterval(sf::milliseconds(20));
}
void InputDeviceStreamer::onConnect(sf::IpAddress IP) {
    start();
    sf::Packet Packet;
    Packet<<(sf::Uint8)StreamMeta<<(sf::Uint8)2<<(sf::Uint32)getSampleRate();
    m_SocketOut.send(Packet,IP,18500);
}
void InputDeviceStreamer::onDisconnect() {
    stop();
}
bool InputDeviceStreamer::onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount) {
    if(SampleCount>40000) return true;
    std::vector<sf::Int16> SampleVec(SampleCount);
    for(int i=0;i<SampleCount;i++)
        SampleVec[i]=Samples[i];
    sendSamples(SampleVec);
    return true;
}

OutputDeviceStreamer::OutputDeviceStreamer() : m_NumUsed(0), m_Init(false) {}
void OutputDeviceStreamer::onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate) {
    if(m_Init==false) {
        initialize(ChannelCount,SampleRate);
        play();
        m_Init=true;
    }
}
void OutputDeviceStreamer::onPacket(sf::Uint8 Type,sf::Packet& Packet) {
    
}
bool OutputDeviceStreamer::onGetData(Chunk& data) {
    while(m_UsingSamples==true) { sf::sleep(sf::milliseconds(1)); }
    m_UsingSamples=true;
    m_Samples.erase(m_Samples.begin(),m_Samples.begin()+m_NumUsed);
    if(m_Samples.size()>=4096) {
        m_UsingSamples=false;
        data.samples=m_Samples.data();
        data.sampleCount=4096;
        m_NumUsed=4096;
    }
    else {
        std::vector<sf::Int16> Backup;
        Backup.resize(1024,0);
        m_Samples.insert(m_Samples.begin(),Backup.begin(),Backup.end());
        m_UsingSamples=false;
        data.samples=m_Samples.data();
        data.sampleCount=1024;
        m_NumUsed=1024;
    }
    return true;
}
void OutputDeviceStreamer::onSeek(sf::Time timeOffset) {
    
}
void OutputDeviceStreamer::onSamples(std::vector<sf::Int16>& Samples) {
    while(m_UsingSamples==true) { sf::sleep(sf::milliseconds(1)); }
    m_UsingSamples=true;
    m_Samples.insert(m_Samples.end(),Samples.begin(),Samples.end());
    if(m_Samples.size()>(getSampleRate()*getChannelCount())*m_BufferSize.asSeconds()) m_Samples.erase(m_Samples.begin(),m_Samples.end()-((getSampleRate()*getChannelCount())*m_BufferSize.asSeconds()));
    m_UsingSamples=false;
}
