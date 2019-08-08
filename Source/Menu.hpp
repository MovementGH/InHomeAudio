#ifndef Menu_hpp
#define Menu_hpp
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.hpp"

class MenuManager;

class Menu {
public:
    Menu(MenuManager* Manager);
    
    virtual void onEvent(sf::Event& Event);
    virtual void onForeground(sf::Time Delta);
    virtual void onLoseFocus();
    virtual void onBackground(sf::Time Delta);
    virtual void onGainFocus();
    virtual void onExit();
    
protected:
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
protected:
    std::vector<Menu*> m_MenuStack;
    sf::RenderWindow& m_Window;
    InputManager m_Input;
    AssetManager m_Assets;
    bool m_Pushed,m_HasFocus;
};

#endif /* Menu_hpp */
