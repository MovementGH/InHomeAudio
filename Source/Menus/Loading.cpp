#include "Loading.hpp"

namespace Menus {
    LoadingMenu::LoadingMenu(MenuManager* Manager):Menu(Manager),m_Loops(0),
    m_LoadingTexture(Manager->getAssets().getAsset<sf::Texture>(resourcePath()+"Loading.png")) {
        m_Loading.setTexture(m_LoadingTexture);
        m_Loading.setOrigin(m_LoadingTexture.getSize().x/2,m_LoadingTexture.getSize().y/2);
        m_Loading.setPosition(m_Manager->getWindow().getSize().x/2,(float)m_Manager->getWindow().getSize().y*.4f);
    }
    void LoadingMenu::onGainFocus() {
        if(m_Loops>=1) m_Loops=-1;
    }
    void LoadingMenu::onForeground(sf::Time Delta) {
        if(m_Loops==-1) {
            m_Manager->popMenu();
            return;
        }
        m_Manager->getWindow().draw(m_Loading);
        if(m_Loops==1)  m_Manager->pushMenu(new Menus::ModeSelection(m_Manager));
        if(m_Loops<2) m_Loops++;
    }
    void LoadingMenu::onBackground(sf::Time Delta) {
        m_Manager->getWindow().draw(m_Loading);
    }
}
