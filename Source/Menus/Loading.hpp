#ifndef Loading_hpp
#define Loading_hpp
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "ModeSelection.hpp"
#include "ResourcePath.hpp"

namespace Menus {
    class LoadingMenu : public Menu {
    public:
        LoadingMenu(MenuManager* Manager);
        virtual void onForeground(sf::Time Delta);
        virtual void onBackground(sf::Time Delta);
        virtual void onGainFocus();
    protected:
        int m_Loops;
        sf::Sprite m_Loading;
        sf::Texture& m_LoadingTexture;
    };
}

#endif /* Loading_hpp */
