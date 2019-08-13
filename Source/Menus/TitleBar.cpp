#include "TitleBar.hpp"
namespace Menus {
    TitleBar::TitleBar(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName,true),m_ArrowButton(m_Manager->getInput()),
    m_Font(Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")),
    m_BackgroundTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Background.jpg")),
    m_ArrowTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Arrow.png")) {
        m_BackgroundTexture.setSmooth(true);
        m_Background.setTexture(m_BackgroundTexture);
        m_Background.setOrigin(m_BackgroundTexture.getSize().x/2,m_BackgroundTexture.getSize().y/2);
        m_Title.setFont(m_Font);
        m_Title.setCharacterSize(48);
        m_Line.setPosition(0,117);
        m_ArrowTexture.setSmooth(true);
        m_Arrow.setTexture(m_ArrowTexture);
        m_Arrow.setOrigin(m_ArrowTexture.getSize().x/2,m_ArrowTexture.getSize().y/2);
        m_Arrow.rotate(180);
        if(isMobile())
            m_Arrow.setPosition(33,75),
            m_Arrow.setScale(.60,.60);
        else
            m_Arrow.setPosition(58,55),
            m_Arrow.setScale(.90,.90);
        m_ArrowButton.Bind(m_Arrow);
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
        if(m_Manager->getMenuStack().size()>2)
            m_Render.draw(m_Arrow);
        m_Render.display();
    }
    void TitleBar::update(sf::Time Delta,bool Foreground) {
        bool ButtonChanged=false;
        if(m_Manager->getMenuStack().size()>2) {
            if(m_ArrowButton.Hovering()&&m_Arrow.getScale().x<1.1*(isMobile()?.6:.9))
                m_Arrow.scale(1.02,1.02),
                ButtonChanged=true;
            if(m_ArrowButton.Hovering()==false&&m_Arrow.getScale().x>(isMobile()?.6:.9))
                m_Arrow.scale(.98,.98),
                ButtonChanged=true;
            if(m_ArrowButton.Clicked())
                m_Manager->popMenu();
        }
        if(m_Title.getString()!=sf::String(m_Manager->getForegroundMenu()->getName())||ButtonChanged) render();
        if(m_Manager->getForegroundMenu()==this) m_Manager->popMenu();
    }
}
