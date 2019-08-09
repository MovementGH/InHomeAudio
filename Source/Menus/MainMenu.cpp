#include "MainMenu.hpp"
namespace Menus {
    MainMenu::MainMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName),
        m_Font(m_Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")),
        m_ArrowTexture(m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Arrow.png")),
        m_CreateTexture(m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Create.png")),
        m_CreateButton(m_Manager->getInput()) {
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Windows.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Mac.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Linux.png"));
        m_PlatformIcons.push_back(&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"iOS.png"));
        m_CreateSprite.setTexture(m_CreateTexture);
        m_CreateSprite.setOrigin(m_CreateTexture.getSize().x/2,m_CreateTexture.getSize().y/2);
    }
    void MainMenu::createMenu(sf::Vector2u WindowSize) {
        m_Manager->getDiscovery().setDiscoverable(true);
        if(isMobile())
            m_CreateSprite.setPosition(WindowSize.x-60,75),
            m_CreateSprite.setScale(.70,.70);
        else
            m_CreateSprite.setPosition(WindowSize.x-60,55);
        m_CreateButton.Bind(m_CreateSprite);
        m_DeviceScroll.setArea({0,120,WindowSize.x+0.f,WindowSize.y-120.f},WindowSize);
        m_DeviceOutlines.clear();
        if(m_Manager->getMenuStack()[m_Manager->getMenuStack().size()-1]==this)
            updateDevices(),
            render();
    }
    void MainMenu::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void MainMenu::render() {
        m_Render.clear(sf::Color::Transparent);
        m_Render.draw(m_CreateSprite);
        m_DeviceScroll.update(m_Manager->getInput());
        m_Render.setView(m_DeviceScroll.getView());
        for(int i=0;i<m_DeviceOutlines.size();i++) {
            m_Render.draw(m_DeviceOutlines[i]);
            m_Render.draw(m_DeviceSprites[i]);
            m_Render.draw(m_DeviceNames[i]);
            m_Render.draw(m_DeviceModes[i]);
            m_Render.draw(m_DeviceArrows[i]);
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
            m_DeviceButtons.resize(Devices.size(),{m_Manager->getInput()});
            m_DeviceSprites.resize(Devices.size());
            m_DeviceNames.resize(Devices.size());
            m_DeviceModes.resize(Devices.size());
            m_DeviceArrows.resize(Devices.size());
            m_DeviceScroll.setHeight(m_DeviceSprites.size()*275);
            for(int i=0;i<m_DeviceSprites.size();i++) {
                m_DeviceOutlines[i].setSize({m_Manager->getWindow().getSize().x+0.f,275});
                m_DeviceOutlines[i].setPosition(10000,i*275);
                m_DeviceOutlines[i].setFillColor(sf::Color(0,0,0,64));
                m_DeviceOutlines[i].setOutlineThickness(1);
                m_DeviceButtons[i].Bind(m_DeviceOutlines[i]);
                m_DeviceSprites[i].setTexture(*m_PlatformIcons[Devices[i].platform]);
                m_DeviceSprites[i].setOrigin(0,0);
                m_DeviceSprites[i].setPosition(10020,10+i*275);
                m_DeviceNames[i].setFont(m_Font);
                m_DeviceNames[i].setCharacterSize(36);
                m_DeviceNames[i].setString(Devices[i].name);
                int Times=0;
                while(m_DeviceNames[i].getLocalBounds().width>m_Manager->getWindow().getSize().x-385&&Times<100)
                    m_DeviceNames[i].setString(m_DeviceNames[i].getString().toAnsiString().substr(0,m_DeviceNames[i].getString().getSize()-4)+"..."),Times++;
                m_DeviceNames[i].setPosition(10300,133+i*275);
                m_DeviceNames[i].setOrigin(0,m_DeviceNames[i].getLocalBounds().height);
                m_DeviceModes[i].setFont(m_Font);
                m_DeviceModes[i].setCharacterSize(24);
                m_DeviceModes[i].setString("Voice Chat");
                m_DeviceModes[i].setPosition(10300,143+i*275);
                m_DeviceArrows[i].setTexture(m_ArrowTexture);
                m_DeviceArrows[i].setPosition(m_Manager->getWindow().getSize().x+10000,137.5+i*275);
                m_DeviceArrows[i].setOrigin(m_ArrowTexture.getSize().x,m_ArrowTexture.getSize().y/2);
            }
            return true;
        }
        return false;
    }
    void MainMenu::onLoseFocus() {
        if(m_Manager->getForegroundMenu()!=this)
            m_CreateSprite.move(100000,0),
            render();
    }
    void MainMenu::onGainFocusComplete() {
        if(m_Manager->getForegroundMenu()!=this)
            m_CreateSprite.move(-100000,0),
            render();
    }
    void MainMenu::update(sf::Time Delta,bool Foreground) {
        if(Foreground) {
            bool ButtonChanged=false;
            if(m_CreateButton.Hovering()&&m_CreateSprite.getScale().x<1.1*(isMobile()?.7:1))
                m_CreateSprite.scale(1.02,1.02),
                ButtonChanged=true;
            if(m_CreateButton.Hovering()==false&&m_CreateSprite.getScale().x>(isMobile()?.7:1))
                m_CreateSprite.scale(.98,.98),
                ButtonChanged=true;
            if(m_CreateButton.Clicked())
                m_Manager->pushMenu(new ModeSelection(m_Manager),new MenuTransitions::Slide(MenuTransitions::Slide::Right,.1),new MenuTransitions::Slide(MenuTransitions::Slide::Left,.1));
            m_Render.setView(m_DeviceScroll.getView());
            for(int i=0;i<m_DeviceButtons.size();i++) {
                if(m_DeviceButtons[i].Hovering(&m_Render)&&m_DeviceOutlines[i].getFillColor()!=sf::Color(0,0,0,128))
                    m_DeviceOutlines[i].setFillColor(sf::Color(0,0,0,128)),
                    ButtonChanged=true;
                else if(m_DeviceButtons[i].Hovering(&m_Render)==false&&m_DeviceOutlines[i].getFillColor()!=sf::Color(0,0,0,64))
                    m_DeviceOutlines[i].setFillColor(sf::Color(0,0,0,64)),
                    ButtonChanged=true;
            }
            m_Render.setView(m_Render.getDefaultView());
            
            if(updateDevices()||m_Manager->getInput().getScrollSpeed()!=0||ButtonChanged) render();
        }
    }
}
