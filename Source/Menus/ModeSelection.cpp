#include "ModeSelection.hpp"
namespace Menus {
    ModeSelection::ModeSelection(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName) {
        std::vector<std::string> ModeFiles={"VoiceCall.png","Media.png","Speaker.png","Microphone.png"};
        m_ModeTextures.resize(ModeFiles.size());
        m_ModeSprites.resize(ModeFiles.size());
        m_ModeButtons.resize(ModeFiles.size(),{m_Manager->getInput()});
        for(int i=0;i<m_ModeSprites.size();i++) {
            m_ModeTextures[i]=&m_Manager->getAssets().getAsset<sf::Texture>(resourcePath()+ModeFiles[i]);
            m_ModeTextures[i]->setSmooth(true);
            m_ModeSprites[i].setTexture(*m_ModeTextures[i]);
            m_ModeSprites[i].setOrigin(m_ModeTextures[i]->getSize().x/2,m_ModeTextures[i]->getSize().y/2);
        }
    }
    void ModeSelection::createMenu(sf::Vector2u WindowSize) {
        m_ModeScroll.setArea({0,120,WindowSize.x-0.f,WindowSize.y-120.f},WindowSize);
        int Rows=std::max(((WindowSize.x-(WindowSize.x%275))/275),(unsigned)1);
        int Cols=ceil((float)m_ModeSprites.size()/Rows);
        m_ModeScroll.setHeight(Cols*325+20);
        for(int i=0;i<m_ModeSprites.size();i++) {
            m_ModeSprites[i].setPosition(WindowSize.x/2-(137*Rows)+(275*(i%Rows))+m_ModeTextures[i]->getSize().x/2+10000,160+(((i-(i%Rows))/Rows)*325));
            m_ModeButtons[i].Bind(m_ModeSprites[i]);
        }
        render();
    }
    void ModeSelection::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void ModeSelection::render() {
        m_Render.clear(sf::Color::Transparent);
        m_ModeScroll.update(m_Manager->getInput());
        m_Render.setView(m_ModeScroll.getView());
        for(int i=0;i<m_ModeSprites.size();i++) m_Render.draw(m_ModeSprites[i]);
        m_Render.setView(m_Render.getDefaultView());
        m_Render.display();
    }
    void ModeSelection::update(sf::Time Delta,bool Foreground) {
        if(Foreground) {
            bool ButtonChanged=false;
            m_Render.setView(m_ModeScroll.getView());
            for(int i=0;i<m_ModeSprites.size();i++) {
                if(m_ModeButtons[i].Hovering(&m_Render)&&m_ModeSprites[i].getScale().x<1.05)
                    m_ModeSprites[i].scale(1.01,1.01),
                    ButtonChanged=true;
                if(m_ModeButtons[i].Hovering(&m_Render)==false&&m_ModeSprites[i].getScale().x>1)
                    m_ModeSprites[i].scale(.99,.99),
                    ButtonChanged=true;
            }
            m_Render.setView(m_Render.getDefaultView());
            if(ButtonChanged||m_Manager->getInput().getScrollSpeed()) render();
        }
    }
}
