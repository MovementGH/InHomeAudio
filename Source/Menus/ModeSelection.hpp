#ifndef ModeSelection_hpp
#define ModeSelection_hpp
#include <math.h>
#include "../Menu.hpp"
#include "../ResourcePath.hpp"

namespace Menus {
    class ModeSelection : public Menu {
    public:
        ModeSelection(MenuManager* Manager,std::string MenuName="Choose Mode");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onEvent(sf::Event& Event) override;
        virtual void update(sf::Time Delta,bool Foreground) override;
        virtual void render() override;
    protected:
        std::vector<sf::Sprite> m_ModeSprites;
        std::vector<Button> m_ModeButtons;
        ScrollArea m_ModeScroll;
        
        std::vector<sf::Texture*> m_ModeTextures;
    };
}

#endif /* ModeSelection_hpp */
