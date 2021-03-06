#ifndef Devices_hpp
#define Devices_hpp
#include <SFML/Audio.hpp>
#include "Streamer.hpp"

class InputDeviceStreamer : virtual public AudioStreamer, public sf::SoundBufferRecorder {
public:
    InputDeviceStreamer();
protected:
    virtual bool onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount);
    virtual void onConnect(sf::IpAddress IP);
    virtual void onDisconnect();
    bool m_Recording;
};

class OutputDeviceStreamer : virtual public AudioStreamer, public sf::SoundStream {
public:
    OutputDeviceStreamer();
protected:
    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onMeta(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    virtual void onPacket(sf::Uint8 Type,sf::Packet& Packet);
    bool m_UsingSamples,m_Init;
    sf::Uint16 m_NumUsed;
    std::vector<sf::Int16> m_Samples;
};
class DualDeviceStreamerStreamer : public OutputDeviceStreamer, public InputDeviceStreamer {};

#endif /* Devices_hpp */
