#include "ModeSelection.hpp"
namespace Menus {
    ModeSelection::ModeSelection(MenuManager* Manager):Menu(Manager),
    m_Font(Manager->getAssets().getAsset<sf::Font>(resourcePath()+"sansation.ttf")),
    m_BackgroundTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Background.jpg")) {
        m_Background.setTexture(m_BackgroundTexture);
        if(isMobile()) m_Background.rotate(90);
        m_Background.setOrigin(m_BackgroundTexture.getSize().x/2,m_BackgroundTexture.getSize().y/2);
        m_Background.setPosition(m_Manager->getWindow().getSize().x/2,m_Manager->getWindow().getSize().y/2);
        float Scale=((float)m_Manager->getWindow().getSize().x/(float)m_Manager->getWindow().getSize().y>(float)m_BackgroundTexture.getSize().x/(float)m_BackgroundTexture.getSize().y)?
                    ((float)m_Manager->getWindow().getSize().x/(float)m_BackgroundTexture.getSize().x):
                    ((float)m_Manager->getWindow().getSize().y/(float)m_BackgroundTexture.getSize().y);
        m_Background.setScale(Scale,Scale);
        m_Background.setColor(sf::Color(255,255,255,16));
    }
    void ModeSelection::onEvent(sf::Event& Event) {
        if(Event.type==sf::Event::KeyPressed&&Event.key.code==sf::Keyboard::Escape) m_Manager->popMenu();
    }
    void ModeSelection::onForeground(sf::Time Delta) {
        if(m_Background.getColor().a<255&&Delta.asSeconds()<.1) m_Background.setColor(sf::Color(255,255,255,std::min(m_Background.getColor().a*(1+10*Delta.asSeconds()),255.f)));
        m_Manager->getWindow().draw(m_Background);
    }
    void ModeSelection::onBackground(sf::Time Delta) {
        m_Manager->getWindow().draw(m_Background);
    }
}
