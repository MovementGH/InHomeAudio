#ifndef MainMenu_hpp
#define MainMenu_hpp
#include <math.h>
#include <SFML/Graphics.hpp>
#include "../Menu.hpp"
#include "../UI.hpp"
#include "../Platform.hpp"
#include "../ResourcePath.hpp"

namespace Menus {
    class MainMenu : public Menu {
    public:
        MainMenu(MenuManager* Manager,std::string MenuName="In Home Audio");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onEvent(sf::Event& Event) override;
        virtual void update(sf::Time Delta,bool Foreground) override;
        
    protected:
        std::vector<sf::Sprite> m_DeviceSprites;
        ScrollArea m_DeviceScroll;
        
        std::vector<sf::Texture*> m_PlatformIcons;
    };
}

#endif /* MainMenu_hpp */
