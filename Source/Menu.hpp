#ifndef Menu_hpp
#define Menu_hpp
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.hpp"

class MenuManager;

class Menu {
public:
    Menu(MenuManager* Manager);
    
    virtual void createMenu(sf::Vector2u WindowSize);
    virtual void update(sf::Time Delta,bool Foreground);
    
    virtual void onEvent(sf::Event& Event);
    virtual void onLoseFocus();
    virtual void onGainFocus();
    virtual void onExit();
    
    sf::Sprite& getRender();
protected:
    sf::RenderTexture m_Render;
    sf::Sprite m_RenderSprite;
    MenuManager* m_Manager;
};

class MenuManager {
public:
    MenuManager(sf::RenderWindow& Window);
    
    void run(Menu* Main);
    
    void pushMenu(Menu* Menu);
    void popMenu();
    
    AssetManager& getAssets();
    sf::RenderWindow& getWindow();
    InputManager& getInput();
protected:
    std::vector<Menu*> m_MenuStack;
    sf::RenderWindow& m_Window;
    InputManager m_Input;
    AssetManager m_Assets;
    bool m_Pushed,m_HasFocus;
};

#endif /* Menu_hpp */
