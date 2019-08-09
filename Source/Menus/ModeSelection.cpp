#include "ModeSelection.hpp"
namespace Menus {
    ModeSelection::ModeSelection(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName),
    m_VoiceTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"VoiceCall.png")) {
        m_ModeSprites.resize(10);
        for(int i=0;i<m_ModeSprites.size();i++) {
            m_ModeSprites[i].setTexture(m_VoiceTexture);
            m_ModeSprites[i].setOrigin(m_VoiceTexture.getSize().x/2,m_VoiceTexture.getSize().y/2);
        }
    }
    void ModeSelection::createMenu(sf::Vector2u WindowSize) {
        m_ModeScroll.setArea({0,120,WindowSize.x-0.f,WindowSize.y-120.f},WindowSize);
        int Rows=std::max(((WindowSize.x-(WindowSize.x%275))/275),(unsigned)1);
        int Cols=ceil((float)m_ModeSprites.size()/Rows);
        m_ModeScroll.setHeight(Cols*325+20);
        for(int i=0;i<m_ModeSprites.size();i++) {
            m_ModeSprites[i].setPosition(WindowSize.x/2-(137*Rows)+(275*(i%Rows))+m_VoiceTexture.getSize().x/2+10000,160+(((i-(i%Rows))/Rows)*325));
        }
    }
    void ModeSelection::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void ModeSelection::update(sf::Time Delta,bool Foreground) {
        m_Render.clear(sf::Color::Transparent);
        m_ModeScroll.update(m_Manager->getInput());
        m_Render.setView(m_ModeScroll.getView());
        for(int i=0;i<m_ModeSprites.size();i++) m_Render.draw(m_ModeSprites[i]);
        m_Render.setView(m_Render.getDefaultView());
        m_Render.display();
    }
}
