#include "MainMenu.hpp"
namespace Menus {
    MainMenu::MainMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName) {
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Windows.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Mac.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Linux.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"iOS.png"));
    }
    void MainMenu::createMenu(sf::Vector2u WindowSize) {
        m_Manager->getDiscovery().setDiscoverable(true);
        m_DeviceScroll.setArea({0,120,WindowSize.x+0.f,WindowSize.y-120.f},WindowSize);
    }
    void MainMenu::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void MainMenu::update(sf::Time Delta,bool Foreground) {
        m_Render.clear(sf::Color::Transparent);
        
        std::vector<NetworkDevice> Devices=m_Manager->getDiscovery().getDevices();
        sf::Vector2u WindowSize=m_Manager->getWindow().getSize();
        std::time_t Time;
        std::time(&Time);
        for(int i=0;i<Devices.size();i++) if(Time-Devices[i].lastSeen>2) Devices.erase(Devices.begin()+i), i--;
        m_DeviceSprites.resize(Devices.size());
        int Cols=std::max(((WindowSize.x-(WindowSize.x%275))/275),(unsigned)1),Rows=ceil((float)m_DeviceSprites.size()/Rows);
        m_DeviceScroll.setHeight(Rows*325+20);
        m_DeviceScroll.update(m_Manager->getInput());
        m_Render.setView(m_DeviceScroll.getView());
        for(int i=0;i<m_DeviceSprites.size();i++) {
            m_DeviceSprites[i].setTexture(*m_PlatformIcons[Devices[i].platform]);
            m_DeviceSprites[i].setOrigin(128,1);
            m_DeviceSprites[i].setPosition(WindowSize.x/2-(137*Cols)+(275*(i%Cols))+m_PlatformIcons[Devices[i].platform]->getSize().x/2+10000,160+(((i-(i%Cols))/Cols)*325));
            m_Render.draw(m_DeviceSprites[i]);
        }
        m_Render.setView(m_Render.getDefaultView());
        m_Render.display();
    }
}
