#ifndef Menu_hpp
#define Menu_hpp
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "NetworkDiscovery.hpp"

class MenuManager;

class Menu {
public:
    Menu(MenuManager* Manager,std::string MenuName="Menu");
    
    virtual void createRender(sf::Vector2u WindowSize,bool Pop,sf::Vector2u StartPos);
    
    virtual void createMenu(sf::Vector2u WindowSize);
    virtual void update(sf::Time Delta,bool Foreground);
    virtual void render();
    
    virtual void onLaunch();
    virtual void onEvent(sf::Event& Event);
    virtual void onLoseFocus();
    virtual void onGainFocus();
    virtual void onExit();
    
    sf::Sprite& getRender();
    std::string getName();
protected:
    sf::RenderTexture m_Render;
    sf::Sprite m_RenderSprite;
    MenuManager* m_Manager;
    std::string m_Name;
};

class MenuManager {
public:
    MenuManager(sf::RenderWindow& Window);
    
    void run(Menu* Main);
    
    void pushMenu(Menu* Menu,bool Pop=false,sf::Vector2u StartPos={0,0});
    void popMenu();
    
    AssetManager& getAssets();
    InputManager& getInput();
    NetworkDiscovery& getDiscovery();
    sf::RenderWindow& getWindow();
    std::vector<Menu*>& getMenuStack();
protected:
    std::vector<Menu*> m_MenuStack;
    sf::RenderWindow& m_Window;
    InputManager m_Input;
    AssetManager m_Assets;
    NetworkDiscovery m_Discovery;
    bool m_Pushed,m_HasFocus;
};

#endif /* Menu_hpp */
