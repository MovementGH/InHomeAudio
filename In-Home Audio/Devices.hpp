//
//  Devices.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Devices_hpp
#define Devices_hpp
#include <vector>
#include <SFML/Audio.hpp>
#include "Streamer.hpp"

class InputDeviceStreamer : public AudioStreamer, public sf::SoundBufferRecorder {
public:
    InputDeviceStreamer();
protected:
    virtual bool onProcessSamples(const sf::Int16* Samples,std::size_t SampleCount);
    virtual void onConnect(sf::IpAddress IP);
};

class OutputDeviceStreamer : public AudioStreamer, public sf::SoundStream {
public:
    OutputDeviceStreamer();
protected:
    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);
    virtual void onSamples(std::vector<sf::Int16> &Samples);
    virtual void onGetStats(sf::Uint8 ChannelCount,sf::Uint32 SampleRate);
    bool m_UsingSamples;
    sf::Uint16 m_NumUsed;
    std::vector<sf::Int16> m_Samples;
};

#endif /* Devices_hpp */
