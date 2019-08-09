#include "Menu.hpp"
Menu::Menu(MenuManager* Manager,std::string MenuName):m_Manager(Manager),m_Name(MenuName){
}
void Menu::createRender(sf::Vector2u WindowSize,bool Pop,sf::Vector2u StartPos) {
    m_Render.create(WindowSize.x,WindowSize.y);
    m_RenderSprite.setPosition((sf::Vector2f)StartPos);
    m_RenderSprite.setOrigin((sf::Vector2f)StartPos);
    m_RenderSprite.setTexture(m_Render.getTexture());
    m_RenderSprite.setTextureRect({0,0,(int)m_Render.getSize().x,(int)m_Render.getSize().y});
    if(Pop) m_RenderSprite.setScale(.1,.1);
}
void Menu::onLaunch(){}
void Menu::render(){}
void Menu::createMenu(sf::Vector2u WindowSize){}
void Menu::onEvent(sf::Event& Event){}
void Menu::onGainFocus(){}
void Menu::update(sf::Time Delta,bool Foreground){}
void Menu::onLoseFocus(){}
void Menu::onExit(){}
std::string Menu::getName() { return m_Name; }
sf::Sprite& Menu::getRender() { return m_RenderSprite; }

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
                    m_MenuStack[i]->createRender({Event.size.width,Event.size.height},false,{Event.size.width/2,Event.size.height/2});
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
                sf::Sprite& Render=m_MenuStack[i]->getRender();
                if(Render.getScale().x<1)
                    Render.setScale(std::min(1.f,Render.getScale().x*1.3f),std::min(1.f,Render.getScale().x*1.3f));
                m_Window.draw(Render);
            }
            m_Window.display();
        }
        if(m_HasFocus==false) sf::sleep(sf::seconds(1));
    }
}
void MenuManager::pushMenu(Menu* Menu,bool Pop,sf::Vector2u StartPos) {
    if(StartPos.x==0&&StartPos.y==0) StartPos=m_Window.getSize()/(unsigned)2;
    if(m_MenuStack.size()) m_MenuStack[m_MenuStack.size()-1]->onLoseFocus();
    m_MenuStack.push_back(Menu);
    Menu->onLaunch();
    Menu->createRender(m_Window.getSize(),Pop,StartPos);
    Menu->createMenu(m_Window.getSize());
    Menu->onGainFocus();
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
InputManager& MenuManager::getInput(){return m_Input;}
NetworkDiscovery& MenuManager::getDiscovery(){return m_Discovery;}
sf::RenderWindow& MenuManager::getWindow(){return m_Window;}
std::vector<Menu*>& MenuManager::getMenuStack(){return m_MenuStack;}
