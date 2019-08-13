#include "Speaker.hpp"

namespace Menus {
    namespace Modes {
        
        Speaker::Speaker(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName) {
            m_Manager->getDiscovery().setDiscoverable(true);
            m_Manager->getDiscovery().setStatus("Speaker");
        }
        void Speaker::createMenu(sf::Vector2u WindowSize) {
            
        }
        void Speaker::onEvent(sf::Event& Event) {
            if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
        }
        void Speaker::onExit() {
            m_Manager->getDiscovery().setDiscoverable(false);
        }
        void Speaker::render() {
            
        }
        void Speaker::update(sf::Time Delta,bool Foreground) {
            
        }
    }
}
