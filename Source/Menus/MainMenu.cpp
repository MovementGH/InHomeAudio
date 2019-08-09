#include "MainMenu.hpp"
namespace Menus {
    MainMenu::MainMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName),
        m_Font(m_Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")) {
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Windows.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Mac.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Linux.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"iOS.png"));
    }
    void MainMenu::createMenu(sf::Vector2u WindowSize) {
        m_Manager->getDiscovery().setDiscoverable(true);
        m_DeviceScroll.setArea({0,120,WindowSize.x+0.f,WindowSize.y-120.f},WindowSize);
        m_DeviceOutlines.clear();
        updateDevices();
        render();
    }
    void MainMenu::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void MainMenu::render() {
        m_Render.clear(sf::Color::Transparent);
        m_DeviceScroll.update(m_Manager->getInput());
        m_Render.setView(m_DeviceScroll.getView());
        for(int i=0;i<m_DeviceOutlines.size();i++) {
            m_Render.draw(m_DeviceOutlines[i]);
            m_Render.draw(m_DeviceSprites[i]);
            m_Render.draw(m_DeviceNames[i]);
            m_Render.draw(m_DeviceModes[i]);
        }
        m_Render.setView(m_Render.getDefaultView());
        m_Render.display();
    }
    bool MainMenu::updateDevices() {
        std::vector<NetworkDevice> Devices=m_Manager->getDiscovery().getDevices();
        std::time_t Time;
        std::time(&Time);
        for(int i=0;i<Devices.size();i++) if(Time-Devices[i].lastSeen>2) Devices.erase(Devices.begin()+i), i--;
        if(Devices.size()!=m_DeviceOutlines.size()) {
            m_DeviceOutlines.resize(Devices.size());
            m_DeviceSprites.resize(Devices.size());
            m_DeviceNames.resize(Devices.size());
            m_DeviceModes.resize(Devices.size());
            m_DeviceScroll.setHeight(m_DeviceSprites.size()*275);
            for(int i=0;i<m_DeviceSprites.size();i++) {
                m_DeviceOutlines[i].setSize({m_Manager->getWindow().getSize().x+0.f,275});
                m_DeviceOutlines[i].setPosition(10000,i*275);
                m_DeviceOutlines[i].setFillColor(sf::Color(0,0,0,64));
                m_DeviceOutlines[i].setOutlineThickness(1);
                m_DeviceSprites[i].setTexture(*m_PlatformIcons[Devices[i].platform]);
                m_DeviceSprites[i].setOrigin(0,0);
                m_DeviceSprites[i].setPosition(10020,10+i*275);
                m_DeviceNames[i].setFont(m_Font);
                m_DeviceNames[i].setCharacterSize(36);
                m_DeviceNames[i].setString(Devices[i].name);
                int Times=0;
                while(m_DeviceNames[i].getLocalBounds().width>m_Manager->getWindow().getSize().x-375&&Times<100)
                    m_DeviceNames[i].setString(m_DeviceNames[i].getString().toAnsiString().substr(0,m_DeviceNames[i].getString().getSize()-4)+"..."),Times++;
                m_DeviceNames[i].setPosition(10300,133+i*275);
                m_DeviceNames[i].setOrigin(0,m_DeviceNames[i].getLocalBounds().height);
                m_DeviceModes[i].setFont(m_Font);
                m_DeviceModes[i].setCharacterSize(24);
                m_DeviceModes[i].setString("Voice Chat");
                m_DeviceModes[i].setPosition(10300,143+i*275);
            }
            return true;
        }
        return false;
    }
    void MainMenu::update(sf::Time Delta,bool Foreground) {
        if(Foreground&&(updateDevices()||m_Manager->getInput().getScrollSpeed()!=0)) render();
    }
}
