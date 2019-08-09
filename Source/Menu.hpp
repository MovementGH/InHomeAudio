#ifndef Menu_hpp
#define Menu_hpp
#include <vector>
#include "UI.hpp"
#include "NetworkDiscovery.hpp"

class MenuManager;

class MenuTransition {
public:
    virtual void enter(sf::Sprite& RenderSprite);
    virtual void exit(sf::Sprite& RenderSprite);
    virtual void update(sf::Time Delta,sf::Sprite& RenderSprite);
    virtual bool isDone(sf::Sprite& RenderSprite);
    bool isExit();
protected:
    bool m_IsExit;
};
class Menu {
public:
    Menu(MenuManager* Manager,std::string MenuName="Menu",bool BackgroundActivity=false);
    ~Menu();
    
    void createRender(sf::Vector2u WindowSize,MenuTransition* Transition=nullptr);
    void focusTransition(MenuTransition* Transition=new MenuTransition());
    void focusTransitionExit();
    void updateTransition(sf::Time Delta);
    void exit(bool UseTransition=true);
    
    sf::Sprite& getRender();
    std::string getName();
    bool getExiting();
    bool transitionIsDone();
    bool hasBackgroundActivity();
    
    virtual void createMenu(sf::Vector2u WindowSize);
    virtual void update(sf::Time Delta,bool Foreground);
    virtual void render();
    
    virtual void onLaunch();
    virtual void onEvent(sf::Event& Event);
    virtual void onLoseFocus();
    virtual void onLoseFocusComplete();
    virtual void onGainFocus();
    virtual void onGainFocusComplete();
    virtual void onExit();
protected:
    MenuManager* m_Manager;
    sf::RenderTexture m_Render;
    sf::Sprite m_RenderSprite;
    std::string m_Name;
private:
    MenuTransition *m_Transition,*m_FocusTransition;
    bool m_Exiting,m_NotifiedFocus,m_BackgroundActivity;
};

class MenuManager {
public:
    MenuManager(sf::RenderWindow& Window);
    
    void run(Menu* Main);
    
    void pushMenu(Menu* Menu,MenuTransition* Transition=nullptr,MenuTransition* FocusTransition=new MenuTransition());
    void popMenu(bool UseTransition=true);
    
    Menu* getForegroundMenu();
    
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
