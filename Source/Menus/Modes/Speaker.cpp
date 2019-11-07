#include "Speaker.hpp"

namespace Menus {
    namespace Modes {
        
        Speaker::Speaker(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName),m_Connected(false),m_Queried(false),
        m_Font(m_Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")) {
            m_Manager->getDiscovery().setDiscoverable(true);
            m_Manager->getDiscovery().setStatus("Speaker");
            m_Streamer.setBufferSize(sf::seconds(0.2));
            m_Streamer.setCodec<OpusCodec>();
            m_Peer.ip=sf::IpAddress::Any;
            m_Peer.lastSeen=0;
            m_Peer.name="Unknown";
            m_Peer.platform=Platform::Windows;
        }
        void Speaker::createMenu(sf::Vector2u WindowSize) {
            m_DisconnectedText.setFont(m_Font);
            m_DisconnectedText.setCharacterSize(28);
            m_DisconnectedText.setString("Not Connected!");
            m_DisconnectedText.setOrigin(m_DisconnectedText.getLocalBounds().width/2,0);
            m_DisconnectedText.setPosition(WindowSize.x/2,WindowSize.y/2);
            m_ConnectedText.setFont(m_Font);
            m_ConnectedText.setCharacterSize(28);
            m_ConnectedText.setPosition(WindowSize.x/2,WindowSize.y/2);
            render();
        }
        void Speaker::onEvent(sf::Event& Event) {
            if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
        }
        void Speaker::onExit() {
            m_Manager->getDiscovery().setDiscoverable(false);
        }
        void Speaker::render() {
            m_Render.clear(sf::Color::Transparent);
            if(m_Streamer.isConnected()==false)
                m_Render.draw(m_DisconnectedText);
            else {
                m_ConnectedText.setString("Connected to "+m_Peer.name+" at "+m_Peer.ip.toString()+" on "+getPlatformName(m_Peer.platform));
                m_ConnectedText.setOrigin(m_ConnectedText.getLocalBounds().width/2,0);
                m_Render.draw(m_ConnectedText);
            }
            m_Render.display();
        }
        void Speaker::update(sf::Time Delta,bool Foreground) {
            if(Foreground) {
                if(m_Streamer.isConnected()!=m_Connected)
                    render(),
                    m_Connected=m_Streamer.isConnected();
                
                if(m_Connected) {
                    if(m_Peer.lastSeen==0) {
                        const std::vector<NetworkDiscovery::Device*>& Devices=m_Manager->getDiscovery().getDevices();
                        bool Found=false;
                        for(int i=0;i<Devices.size();i++) if(Devices[i]->ip==m_Streamer.getPeerIP()) {
                            m_Peer.lastSeen=Devices[i]->lastSeen;
                            m_Peer.ip=Devices[i]->ip;
                            m_Peer.name=Devices[i]->name;
                            m_Peer.platform=Devices[i]->platform;
                            render();
                            Found=true;
                            std::cout<<(std::string)m_Peer.name<<std::endl;
                        }
                        if(Found==false&&m_Queried==false) m_Manager->getDiscovery().queryDevice(m_Streamer.getPeerIP());
                    }
                }
            }
        }
    }
}
