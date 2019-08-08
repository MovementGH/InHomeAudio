#include "MainMenu.hpp"
namespace Menus {
    MainMenu::MainMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName) {
        
    }
    void MainMenu::createMenu(sf::Vector2u WindowSize) {
        m_Manager->getDiscovery().setDiscoverable(true);
    }
    void MainMenu::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void MainMenu::update(sf::Time Delta,bool Foreground) {
        m_Render.clear(sf::Color::Transparent);
        std::cout<<m_Manager->getDiscovery().getDevices().size()<<std::endl;
        m_Render.display();
    }
}
