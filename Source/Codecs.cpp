#include "Codecs.hpp"

sf::Packet AudioCodec::Encode(std::vector<sf::Int16> &Samples) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)0<<(sf::Uint64)Samples.size();
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
void AudioCodec::Reset(){}

OpusCodec::OpusCodec(int m_Bitrate) {
    int Error=0;
    m_Encoder=opus_encoder_create(48000,2,OPUS_APPLICATION_AUDIO,&Error);
    opus_encoder_ctl(m_Encoder,OPUS_SET_BITRATE(m_Bitrate));
    m_Decoder=opus_decoder_create(48000,2,&Error);
    m_Buffer.resize(0);
    m_Samples.resize(1000);
    m_DecSamples.resize(1000);
}
OpusCodec::~OpusCodec() {
    opus_encoder_destroy(m_Encoder);
    opus_decoder_destroy(m_Decoder);
}
sf::Packet OpusCodec::Encode(std::vector<sf::Int16> &Samples) {
    sf::Packet Packet;
    Samples.insert(Samples.begin(),m_Buffer.begin(),m_Buffer.end());
    sf::Uint16 FrameSize=(Samples.size()>=5760)?2880:((Samples.size()>=3840)?1920:((Samples.size()>=1920?960:((Samples.size()>=960?480:0)))));
    if(FrameSize==0) return Packet<<(sf::Uint8)0<<(sf::Uint8)0;
    m_Buffer.clear();
    m_Buffer.insert(m_Buffer.begin(),Samples.begin()+FrameSize*2,Samples.end());
    Samples.erase(Samples.begin()+FrameSize*2,Samples.end());
    sf::Uint32 DataSize=opus_encode(m_Encoder,Samples.data(),FrameSize,m_Samples.data(),(int)m_Samples.size());
    Packet<<(sf::Uint8)0<<FrameSize<<DataSize;
    for(int i=0;i<DataSize;i++) Packet<<(sf::Uint8)m_Samples[i];
    return Packet;
}
std::vector<sf::Int16> OpusCodec::Decode(sf::Packet &Packet) {
    sf::Uint16 FrameSize;
    sf::Uint32 DataSize;
    Packet>>FrameSize>>DataSize;
    std::vector<sf::Int16> Samples(FrameSize*2);
    for(int i=0;i<DataSize;i++) Packet>>m_DecSamples[i];
    opus_decode(m_Decoder,m_DecSamples.data(),DataSize,Samples.data(),FrameSize,0);
    return Samples;
}
void OpusCodec::Reset() {
    int Error=0;
    opus_encoder_destroy(m_Encoder);
    opus_decoder_destroy(m_Decoder);
    m_Encoder=opus_encoder_create(48000,2,OPUS_APPLICATION_AUDIO,&Error);
    opus_encoder_ctl(m_Encoder,OPUS_SET_BITRATE(m_Bitrate));
    m_Decoder=opus_decoder_create(48000,2,&Error);
}
