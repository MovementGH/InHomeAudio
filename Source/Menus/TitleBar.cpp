#include "TitleBar.hpp"
namespace Menus {
    TitleBar::TitleBar(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName,true),
    m_Font(Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")),
    m_BackgroundTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Background.jpg")) {
        m_Background.setTexture(m_BackgroundTexture);
        m_Background.setOrigin(m_BackgroundTexture.getSize().x/2,m_BackgroundTexture.getSize().y/2);
        m_Title.setFont(m_Font);
        m_Title.setCharacterSize(48);
        m_Line.setPosition(0,117);
    }
    void TitleBar::onLaunch() {
        m_Manager->pushMenu(new MainMenu(m_Manager),isMobile()?(new MenuTransitions::Grow(sf::Vector2f(m_Manager->getWindow().getSize()/(unsigned)2),.3)):nullptr);
    }
    void TitleBar::createMenu(sf::Vector2u WindowSize) {
        if(((float)WindowSize.x/(float)WindowSize.y)<1) m_Background.setRotation(90);
        else m_Background.setRotation(0);
        float BGScale=((float)WindowSize.x/(float)WindowSize.y>(float)m_BackgroundTexture.getSize().x/(float)m_BackgroundTexture.getSize().y)?
        ((float)WindowSize.x/(float)m_BackgroundTexture.getSize().x):
        ((float)WindowSize.y/(float)m_BackgroundTexture.getSize().y);
        m_Background.setPosition(WindowSize.x/2,WindowSize.y/2);
        m_Background.setScale(BGScale,BGScale);
        m_Title.setPosition(WindowSize.x/2,isMobile()?40:25);
        m_Line.setSize({WindowSize.x+0.f,3});
        render();
    }
    void TitleBar::render() {
        m_Title.setString(m_Manager->getForegroundMenu()->getName());
        m_Title.setOrigin(m_Title.getLocalBounds().width/2,0);
        m_Render.clear(sf::Color::Transparent);
        m_Render.draw(m_Background);
        m_Render.draw(m_Title);
        m_Render.draw(m_Line);
        m_Render.display();
    }
    void TitleBar::update(sf::Time Delta,bool Foreground) {
        if(m_Title.getString()!=sf::String(m_Manager->getForegroundMenu()->getName())) render();
        if(m_Manager->getForegroundMenu()==this) m_Manager->popMenu();
    }
}
