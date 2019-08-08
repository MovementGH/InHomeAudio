#ifndef ModeSelection_hpp
#define ModeSelection_hpp
#include <math.h>
#include <SFML/Graphics.hpp>
#include "../Platform.hpp"
#include "../Menu.hpp"
#include "../ResourcePath.hpp"

namespace Menus {
    class ModeSelection : public Menu {
    public:
        ModeSelection(MenuManager* Manager);
        
        virtual void createMenu(sf::Vector2u WindowSize);
        virtual void onEvent(sf::Event& Event);
        virtual void onForeground(sf::Time Delta);
        virtual void onBackground(sf::Time Delta);
    protected:
        sf::Sprite m_Background;
        sf::Text m_Title;
        sf::RectangleShape m_Line;
        std::vector<sf::Sprite> m_ModeSprites;
        ScrollArea m_ModeScroll;
        
        sf::Font& m_Font;
        sf::Texture& m_BackgroundTexture;
        sf::Texture& m_VoiceTexture;
        
    };
}

#endif /* ModeSelection_hpp */
