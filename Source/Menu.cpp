#include "Menu.hpp"
Menu::Menu(MenuManager* Manager):m_Manager(Manager){
}
void Menu::createMenu(sf::Vector2u WindowSize) {
    m_Render.create(WindowSize.x,WindowSize.y);
    m_RenderSprite.setPosition(m_Render.getSize().x/2,m_Render.getSize().y/2);
    m_RenderSprite.setOrigin(m_Render.getSize().x/2,m_Render.getSize().y/2);
    m_RenderSprite.setTexture(m_Render.getTexture());
    m_RenderSprite.setTextureRect({0,0,(int)m_Render.getSize().x,(int)m_Render.getSize().y});
}
void Menu::onEvent(sf::Event& Event){}
void Menu::onGainFocus(){}
void Menu::update(sf::Time Delta,bool Foreground){}
void Menu::onLoseFocus(){}
void Menu::onExit(){}

sf::Sprite& Menu::getRender() {
    return m_RenderSprite;
}

MenuManager::MenuManager(sf::RenderWindow& Window):m_Window(Window),m_HasFocus(true){}
void MenuManager::run(Menu* Main) {
    pushMenu(Main);
    sf::Clock FrameClock;
    while(m_Window.isOpen()) {
        m_Input.Reset();
        m_Pushed=false;
        sf::Event Event;
        while(m_Window.pollEvent(Event)) {
            if(Event.type==sf::Event::Closed) m_Window.close();
            if(Event.type==sf::Event::LostFocus) {
                m_HasFocus=false;
                m_MenuStack[m_MenuStack.size()-1]->onLoseFocus();
            }
            if(Event.type==sf::Event::GainedFocus) {
                m_HasFocus=true;
                m_MenuStack[m_MenuStack.size()-1]->onGainFocus();
            }
            if(Event.type==sf::Event::Resized) {
                sf::View View({0,0,(float)Event.size.width,(float)Event.size.height});
                m_Window.setView(View);
                for(int i=0;i<m_MenuStack.size();i++) {
                    m_MenuStack[i]->Menu::createMenu({Event.size.width,Event.size.height});
                    m_MenuStack[i]->createMenu({Event.size.width,Event.size.height});
                }
            }
            m_Input.Event(Event);
            m_MenuStack[m_MenuStack.size()-1]->onEvent(Event);
            if(m_Pushed) break;
        }
        if(!m_Pushed) {
            m_Window.clear();
            sf::Time Delta=FrameClock.getElapsedTime();
            FrameClock.restart();
            for(int i=0;i<m_MenuStack.size();i++) {
                m_MenuStack[i]->update(Delta,i==m_MenuStack.size()-1);
                m_Window.draw(m_MenuStack[i]->getRender());
            }
            m_Window.display();
        }
        if(m_HasFocus==false) sf::sleep(sf::seconds(1));
    }
}
void MenuManager::pushMenu(Menu* Menu) {
    if(m_MenuStack.size()) m_MenuStack[m_MenuStack.size()-1]->onLoseFocus();
    m_MenuStack.push_back(Menu);
    m_MenuStack[m_MenuStack.size()-1]->createMenu(m_Window.getSize());
    m_MenuStack[m_MenuStack.size()-1]->Menu::createMenu(m_Window.getSize());
    m_Pushed=true;
}
void MenuManager::popMenu() {
    m_MenuStack[m_MenuStack.size()-1]->onExit();
    if(m_MenuStack.size()>1) m_MenuStack[m_MenuStack.size()-2]->onGainFocus();
    delete m_MenuStack[m_MenuStack.size()-1];
    m_MenuStack.pop_back();
    if(m_MenuStack.size()==0) m_Window.close();
    m_Pushed=true;
}
AssetManager& MenuManager::getAssets(){return m_Assets;}
sf::RenderWindow& MenuManager::getWindow(){return m_Window;}
InputManager& MenuManager::getInput(){return m_Input;}
