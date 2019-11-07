#ifndef Speaker_hpp
#define Speaker_hpp
#include "../../ResourcePath.hpp"
#include "../../Transitions.hpp"
#include "../../Devices.hpp"

namespace Menus {
    namespace Modes {
        class Speaker : public Menu {
        public:
            Speaker(MenuManager* Manager,std::string MenuName="Speaker");
            
            virtual void createMenu(sf::Vector2u WindowSize) override;
            virtual void onEvent(sf::Event& Event) override;
            virtual void onExit() override;
            virtual void render() override;
            virtual void update(sf::Time Delta,bool Foreground) override;
        protected:
            sf::Font& m_Font;
            
            OutputDeviceStreamer m_Streamer;
            bool m_Connected,m_Queried;
            
            sf::Text m_DisconnectedText;
            
            sf::Text m_ConnectedText;
            
            NetworkDiscovery::Device m_Peer;
            
        };
    }
}

#endif /* Speaker_hpp */
