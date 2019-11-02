#include "Streamer.hpp"
AudioStreamer::AudioStreamer() : m_Connected(false),m_Listen(true),m_BufferSize(sf::seconds(.2)) {
    m_Codec=new AudioCodec();
    m_SocketOut.setBlocking(false);
    m_SocketIn.setBlocking(true);
    sf::Socket::Status Status=m_SocketIn.bind(StreamerPort);
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
                        if(Type==Connect) {
                            if(m_Connected) disconnect();
                            onConnectRequest(IP);
                        }
                        else if(Type==ConnectAccept) {
                            m_Connected=true;
                            m_IP=IP;
                            onConnect(IP);
                        }
                        else if(Type==ConnectReject)
                            onConnectReject(IP);
                        else if(Type==Audio&&m_Connected) {
                            std::vector<sf::Int16> Samples=m_Codec->Decode(Packet);
                            bool UseSamples=true;
                            for(int i=0;i<m_FilterIn.size();i++)
                                if(m_FilterIn[i]->Filter(Samples)==false)
                                    UseSamples=false;
                            if(UseSamples)
                                onSamples(Samples);
                        }
                        else if(Type==Disconnect) {
                            m_Connected=false;
                            m_Codec->Reset();
                            onDisconnect();
                        }
                        else if(Type==StreamMeta) {
                            sf::Uint8 ChannelCount;
                            sf::Uint32 SampleRate;
                            Packet>>ChannelCount>>SampleRate;
                            onMeta(ChannelCount,SampleRate);
                        }
                        else onPacket(Type,Packet);
                    }
                    else if(Status==sf::Socket::Error)
                        std::cout<<"Socket Error"<<std::endl;
                }
                sf::sleep(sf::milliseconds(10));
            }
        });
    }
    else if(Status==sf::Socket::Error)
        std::cout<<"Binding Error"<<std::endl;
}
AudioStreamer::~AudioStreamer() {
    disconnect();
    m_Listen=false;
    m_WorkerThread->join();
}
void AudioStreamer::connect(sf::IpAddress IP) {
    if(m_Connected==false) {
        sf::Packet Packet;
        Packet<<(sf::Uint8)Connect;
        m_SocketOut.setBlocking(true);
        m_SocketOut.send(Packet,IP,StreamerPort);
        m_SocketOut.setBlocking(false);
    }
}
void AudioStreamer::disconnect() {
    if(m_Connected) {
        sf::Packet Packet;
        Packet<<(sf::Uint8)Disconnect;
        m_SocketOut.setBlocking(true);
        m_SocketOut.send(Packet,m_IP,StreamerPort);
        m_SocketOut.setBlocking(false);
        m_Connected=false;
    }
}
void AudioStreamer::sendSamples(std::vector<sf::Int16> &Samples) {
    if(m_Connected) {
        for(int i=0;i<m_FilterOut.size();i++)
            if(m_FilterOut[i]->Filter(Samples)==false)
                return;
        sf::Packet Packet=m_Codec->Encode(Samples);
        m_SocketOut.send(Packet,m_IP,StreamerPort);
    }
}
void AudioStreamer::sendMeta(sf::Uint8 ChannelCount,sf::Uint32 SampleRate) {
    if(m_Connected) {
        sf::Packet Packet;
        Packet<<StreamMeta<<ChannelCount<<SampleRate;
        m_SocketOut.send(Packet,m_IP,StreamerPort);
    }
}
bool AudioStreamer::isConnected(){return m_Connected;}
void AudioStreamer::setBufferSize(sf::Time Size){m_BufferSize=Size;}
void AudioStreamer::onSamples(std::vector<sf::Int16> &Samples){}
void AudioStreamer::onConnectReject(sf::IpAddress IP){}
void AudioStreamer::onConnect(sf::IpAddress IP){}
void AudioStreamer::onDisconnect(){}
void AudioStreamer::onPacket(sf::Uint8 Type,sf::Packet& Packet){}
void AudioStreamer::onMeta(sf::Uint8 ChannelCount,sf::Uint32 SampleRate){}
void AudioStreamer::onConnectRequest(sf::IpAddress IP) {
    sf::Packet Packet;
    Packet<<(sf::Uint8)ConnectAccept;
    m_SocketOut.send(Packet,IP,StreamerPort);
    m_IP=IP;
    m_Connected=true;
    onConnect(IP);
}
