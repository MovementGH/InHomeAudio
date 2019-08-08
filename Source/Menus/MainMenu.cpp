#include "MainMenu.hpp"
namespace Menus {
    MainMenu::MainMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName) {
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Windows.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Mac.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Linux.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"iOS.png"));
    }
    void MainMenu::createMenu(sf::Vector2u WindowSize) {
    }
    void MainMenu::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void MainMenu::update(sf::Time Delta,bool Foreground) {
        m_Render.clear(sf::Color::Transparent);
        std::vector<NetworkDevice> Devices=m_Manager->getDiscovery().getDevices();
        std::time_t Time;
        std::time(&Time);
        for(int i=0;i<Devices.size();i++) if(Time-Devices[i].lastSeen>1) Devices.erase(Devices.begin()+i), i--;
        m_DeviceSprites.resize(Devices.size());
        for(int i=0;i<Devices.size();i++) {
            m_DeviceSprites[i].setTexture(*m_PlatformIcons[Devices[i].platform]);
            m_DeviceSprites[i].setOrigin(128,128);
            m_DeviceSprites[i].setPosition(200,300);
            m_Render.draw(m_DeviceSprites[i]);
        }
        m_Render.display();
    }
}
