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
        ModeSelection(MenuManager* Manager,std::string MenuName="Choose Mode");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onEvent(sf::Event& Event) override;
        virtual void update(sf::Time Delta,bool Foreground) override;
    protected:
        std::vector<sf::Sprite> m_ModeSprites;
        ScrollArea m_ModeScroll;
        
        sf::Texture& m_VoiceTexture;
    };
}

#endif /* ModeSelection_hpp */
