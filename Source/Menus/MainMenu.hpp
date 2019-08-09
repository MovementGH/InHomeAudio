#ifndef MainMenu_hpp
#define MainMenu_hpp
#include <math.h>
#include <SFML/Graphics.hpp>
#include "../Menu.hpp"
#include "../UI.hpp"
#include "../Platform.hpp"
#include "../ResourcePath.hpp"
#include "ModeSelection.hpp"

namespace Menus {
    class MainMenu : public Menu {
    public:
        MainMenu(MenuManager* Manager,std::string MenuName="In Home Audio");
        
        virtual void createMenu(sf::Vector2u WindowSize) override;
        virtual void onEvent(sf::Event& Event) override;
        virtual void onGainFocus() override;
        virtual void onLoseFocus() override;
        virtual void render() override;
        virtual void update(sf::Time Delta,bool Foreground) override;
        
        bool updateDevices();
    protected:
        std::vector<sf::Sprite> m_DeviceSprites,m_DeviceArrows;
        std::vector<sf::Text> m_DeviceNames,m_DeviceModes;
        std::vector<sf::RectangleShape> m_DeviceOutlines;
        ScrollArea m_DeviceScroll;
        sf::Sprite m_CreateSprite;
        
        Button m_CreateButton;
        
        std::vector<sf::Texture*> m_PlatformIcons;
        sf::Font& m_Font;
        sf::Texture& m_ArrowTexture,m_CreateTexture;
    };
}

#endif /* MainMenu_hpp */
