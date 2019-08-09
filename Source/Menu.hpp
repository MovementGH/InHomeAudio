#ifndef Menu_hpp
#define Menu_hpp
#include <vector>
#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "NetworkDiscovery.hpp"

class MenuManager;

class MenuTransition {
public:
    virtual void init(sf::Sprite& RenderSprite);
    virtual void exit(sf::Sprite& RenderSprite);
    virtual void update(sf::Time Delta,sf::Sprite& RenderSprite);
    virtual bool isDone();
};
class Menu {
public:
    Menu(MenuManager* Manager,std::string MenuName="Menu");
    
    void createRender(sf::Vector2u WindowSize,MenuTransition* Transition=nullptr);
    void updateTransition(sf::Time Delta);
    void exit(bool UseTransition=true);
    
    sf::Sprite& getRender();
    std::string getName();
    bool getExiting();
    bool transitionIsDone();
    
    virtual void createMenu(sf::Vector2u WindowSize);
    virtual void update(sf::Time Delta,bool Foreground);
    virtual void render();
    
    virtual void onLaunch();
    virtual void onEvent(sf::Event& Event);
    virtual void onLoseFocus();
    virtual void onGainFocus();
    virtual void onExit();
protected:
    MenuManager* m_Manager;
    sf::RenderTexture m_Render;
    sf::Sprite m_RenderSprite;
    std::string m_Name;
private:
    MenuTransition* m_Transition;
    bool m_Exiting;
};

class MenuManager {
public:
    MenuManager(sf::RenderWindow& Window);
    
    void run(Menu* Main);
    
    void pushMenu(Menu* Menu,MenuTransition* Transition=nullptr);
    void popMenu(bool UseTransition=true);
    
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
    bool m_StackChanged,m_HasFocus;
};

#endif /* Menu_hpp */
