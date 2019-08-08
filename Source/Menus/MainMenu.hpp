#ifndef MainMenu_hpp
#define MainMenu_hpp
#include <SFML/Graphics.hpp>
#include "../Menu.hpp"

namespace Menus {
    class MainMenu : public Menu {
    public:
        MainMenu(MenuManager* Manager,std::string MenuName="In Home Audio");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onEvent(sf::Event& Event) override;
        virtual void update(sf::Time Delta,bool Foreground) override;
        
    protected:
        
    };
}

#endif /* MainMenu_hpp */
