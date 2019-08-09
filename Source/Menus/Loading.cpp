#include "Loading.hpp"

namespace Menus {
    LoadingMenu::LoadingMenu(MenuManager* Manager,std::string MenuName):Menu(Manager,MenuName),m_Loops(0),
    m_LoadingTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Loading.png")) {
        m_Loading.setTexture(m_LoadingTexture);
        m_Loading.setOrigin(m_LoadingTexture.getSize().x/2,m_LoadingTexture.getSize().y/2);
    }
    void LoadingMenu::createMenu(sf::Vector2u WindowSize) {
        m_Loading.setPosition(WindowSize.x/2,(float)WindowSize.y*.4f);
        m_Render.clear();
        m_Render.draw(m_Loading);
        m_Render.display();
    }
    void LoadingMenu::update(sf::Time Delta,bool Foreground) {
        if(m_Loops) m_Manager->pushMenu(new TitleBar(m_Manager),new MenuTransitions::Grow(sf::Vector2f(m_Manager->getWindow().getSize()/(unsigned)2),.3));
        m_Loops++;
    }
}
