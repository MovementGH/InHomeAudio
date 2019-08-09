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
    void LoadingMenu::onGainFocus() {
        if(m_Loops>=2) m_Loops=-1;
    }
    void LoadingMenu::update(sf::Time Delta,bool Foreground) {
        if(Foreground) {
            if(m_Loops==-1) {
                m_Manager->popMenu();
                return;
            }
            else if(m_Loops==1) m_Manager->pushMenu(new Menus::TitleBar(m_Manager));
            if(m_Loops<2) m_Loops++;
        }
    }
}
