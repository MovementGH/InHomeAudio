#include "ModeSelection.hpp"
namespace Menus {
    ModeSelection::ModeSelection(MenuManager* Manager):Menu(Manager),
    m_Font(Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")),
    m_BackgroundTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Background.jpg")),
    m_VoiceTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"VoiceCall.png")) {
        m_Background.setTexture(m_BackgroundTexture);
        m_Background.setOrigin(m_BackgroundTexture.getSize().x/2,m_BackgroundTexture.getSize().y/2);
        m_Title.setFont(m_Font);
        m_Title.setCharacterSize(48);
        m_Title.setString("In Home Audio");
        m_Title.setOrigin(m_Title.getLocalBounds().width/2,0);
        m_Line.setPosition(0,117);
        m_ModeSprites.resize(10);
        for(int i=0;i<m_ModeSprites.size();i++) {
            m_ModeSprites[i].setTexture(m_VoiceTexture);
            m_ModeSprites[i].setOrigin(m_VoiceTexture.getSize().x/2,m_VoiceTexture.getSize().y/2);
        }
        if(isMobile()) {
            m_Background.setColor(sf::Color(128,128,128,16));
            m_Title.setFillColor(sf::Color(255,255,255,4));
            m_Line.setFillColor(sf::Color(255,255,255,4));
            for(int i=0;i<m_ModeSprites.size();i++)
                m_ModeSprites[i].setColor(sf::Color(255,255,255,4));
        }
        else
            m_Background.setColor(sf::Color(128,128,128,255));
    }
    void ModeSelection::createMenu(sf::Vector2u WindowSize) {
        if(((float)WindowSize.x/(float)WindowSize.y)<1)
            m_Background.setRotation(90);
        else
            m_Background.setRotation(0);
        float BGScale=((float)WindowSize.x/(float)WindowSize.y>(float)m_BackgroundTexture.getSize().x/(float)m_BackgroundTexture.getSize().y)?
        ((float)WindowSize.x/(float)m_BackgroundTexture.getSize().x):
        ((float)WindowSize.y/(float)m_BackgroundTexture.getSize().y);
        m_Background.setPosition(WindowSize.x/2,WindowSize.y/2);
        m_Background.setScale(BGScale,BGScale);
        m_Title.setPosition(WindowSize.x/2,isMobile()?40:25);
        m_Line.setSize({WindowSize.x+0.f,3});
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
        m_Render.clear();
        if(Foreground) {
        if(m_Background.getColor().a<255&&Delta.asSeconds()<.1) m_Background.setColor(sf::Color(128,128,128,std::min(m_Background.getColor().a*(1+10*Delta.asSeconds()),255.f)));
        else if(m_Title.getFillColor().a<255&&Delta.asSeconds()<.1) {
            m_Title.setFillColor(sf::Color(255,255,255,std::min(m_Title.getFillColor().a*(1+20*Delta.asSeconds()),255.f)));
            m_Line.setFillColor(sf::Color(255,255,255,std::min(m_Line.getFillColor().a*(1+20*Delta.asSeconds()),255.f)));
            for(int i=0;i<m_ModeSprites.size();i++)
                m_ModeSprites[i].setColor(sf::Color(255,255,255,std::min(m_ModeSprites[i].getColor().a*(1+20*Delta.asSeconds()),255.f)));
        }
        m_Render.draw(m_Background);
        m_Render.draw(m_Title);
        m_Render.draw(m_Line);
        m_Render.setView(m_ModeScroll.getView());
        m_ModeScroll.update(m_Manager->getInput());
        for(int i=0;i<m_ModeSprites.size();i++) m_Render.draw(m_ModeSprites[i]);
        m_Render.setView(m_Render.getDefaultView());
        }
        else m_Render.draw(m_Background);
        m_Render.display();
    }
}
