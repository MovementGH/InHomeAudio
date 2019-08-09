#ifndef ModeSelection_hpp
#define ModeSelection_hpp
#include <SFML/Graphics.hpp>
#include "../Platform.hpp"
#include "../Menu.hpp"
#include "../ResourcePath.hpp"
#include "MainMenu.hpp"

namespace Menus {
    class TitleBar : public Menu {
    public:
        TitleBar(MenuManager* Manager,std::string MenuName="");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onLaunch() override;
        virtual void render() override;
        virtual void update(sf::Time Delta,bool Foreground) override;
    protected:
        sf::Sprite m_Background;
        sf::Text m_Title;
        sf::RectangleShape m_Line;
        
        sf::Font& m_Font;
        sf::Texture& m_BackgroundTexture;
    };
}

#endif /* ModeSelection_hpp */
