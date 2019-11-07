#ifndef Codecs_hpp
#define Codecs_hpp
#include <vector>
#include <opus.h>
#include <SFML/Network.hpp>

class AudioCodec {
public:
    virtual sf::Packet Encode(std::vector<sf::Int16> &Samples);
    virtual std::vector<sf::Int16> Decode(sf::Packet &Packet);
    virtual void Reset();
};

class OpusCodec : public AudioCodec {
public:
    OpusCodec(int m_Bitrate=42000);
    ~OpusCodec();
    virtual sf::Packet Encode(std::vector<sf::Int16> &Samples);
    virtual std::vector<sf::Int16> Decode(sf::Packet &Packet);
    virtual void Reset();
    OpusEncoder* m_Encoder;
    OpusDecoder* m_Decoder;
    std::vector<sf::Uint8> m_Samples,m_DecSamples;
    std::vector<sf::Int16> m_Buffer;
    int m_Bitrate;
};

#endif /* Codecs_hpp */
