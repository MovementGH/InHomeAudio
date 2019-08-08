#include "Menu.hpp"
Menu::Menu(MenuManager* Manager):m_Manager(Manager){}
void Menu::onEvent(sf::Event& Event){}
void Menu::onGainFocus(){}
void Menu::onForeground(sf::Time Delta){}
void Menu::onBackground(sf::Time Delta){}
void Menu::onLoseFocus(){}
void Menu::onExit(){}

MenuManager::MenuManager(sf::RenderWindow& Window):m_Window(Window),m_HasFocus(true){}
void MenuManager::run(Menu* Main) {
    pushMenu(Main);
    sf::Clock FrameClock;
    while(m_Window.isOpen()) {
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
            m_Input.Event(Event);
            m_MenuStack[m_MenuStack.size()-1]->onEvent(Event);
            if(m_Pushed) break;
        }
        if(!m_Pushed) {
            m_Window.clear();
            sf::Time Delta=FrameClock.getElapsedTime();
            FrameClock.restart();
            for(int i=0;i<m_MenuStack.size()-(m_HasFocus?1:0);i++) m_MenuStack[i]->onBackground(Delta);
            if(m_HasFocus) m_MenuStack[m_MenuStack.size()-1]->onForeground(Delta);
            m_Window.display();
        }
        if(m_HasFocus==false) sf::sleep(sf::seconds(1));
    }
}
void MenuManager::pushMenu(Menu* Menu) {
    if(m_MenuStack.size()) m_MenuStack[m_MenuStack.size()-1]->onLoseFocus();
    m_MenuStack.push_back(Menu);
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
