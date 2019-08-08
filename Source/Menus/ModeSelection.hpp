#ifndef ModeSelection_hpp
#define ModeSelection_hpp
#include <SFML/Graphics.hpp>
#include "../Platform.hpp"
#include "../Menu.hpp"
#include "../ResourcePath.hpp"

namespace Menus {
    class ModeSelection : public Menu {
    public:
        ModeSelection(MenuManager* Manager);
        
        virtual void onEvent(sf::Event& Event);
        virtual void onForeground(sf::Time Delta);
        virtual void onBackground(sf::Time Delta);
    protected:
        sf::Sprite m_Background;
        
        sf::Font& m_Font;
        sf::Texture& m_BackgroundTexture;
    };
}

#endif /* ModeSelection_hpp */
