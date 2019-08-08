#ifndef Loading_hpp
#define Loading_hpp
#include <SFML/Graphics.hpp>
#include "../Menu.hpp"
#include "../Platform.hpp"
#include "../ResourcePath.hpp"
#include "TitleBar.hpp"

namespace Menus {
    class LoadingMenu : public Menu {
    public:
        LoadingMenu(MenuManager* Manager,std::string MenuName="");
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void update(sf::Time Delta,bool Foreground) override;
        virtual void onGainFocus() override;
    protected:
        int m_Loops;
        sf::Sprite m_Loading;
        sf::Texture& m_LoadingTexture;
    };
}

#endif /* Loading_hpp */
