#include "Menu.hpp"
void MenuTransition::init(sf::Sprite& RenderSptire){}
void MenuTransition::exit(sf::Sprite& RenderSprite){}
void MenuTransition::update(sf::Time Delta,sf::Sprite& RenderSprite){}
bool MenuTransition::isDone(){return true;}
Menu::Menu(MenuManager* Manager,std::string MenuName):m_Manager(Manager),m_Name(MenuName),m_Transition(nullptr){}
void Menu::createRender(sf::Vector2u WindowSize,MenuTransition* Transition) {
    m_Render.create(WindowSize.x,WindowSize.y);
    m_RenderSprite.setTexture(m_Render.getTexture());
    bool UseTransition=false;
    if(Transition==nullptr) {
        if(m_Transition==nullptr)
            m_Transition=new MenuTransition(),
            UseTransition=true;
    }
    else {
        delete m_Transition;
        m_Transition=Transition;
        UseTransition=true;
    }
    if(UseTransition)
        m_Transition->init(m_RenderSprite);
}
void Menu::updateTransition(sf::Time Delta){m_Transition->update(Delta,m_RenderSprite);}
void Menu::exit(bool UseTransition) {
    if(UseTransition) {
        m_Exiting=true;
        m_Transition->exit(m_RenderSprite);
    }
}
bool Menu::getExiting(){return m_Exiting;}
bool Menu::transitionIsDone(){return m_Transition&&m_Transition->isDone();}
std::string Menu::getName() {return m_Name;}
sf::Sprite& Menu::getRender() {return m_RenderSprite;}
void Menu::createMenu(sf::Vector2u WindowSize){}
void Menu::update(sf::Time Delta,bool Foreground){}
void Menu::render(){}
void Menu::onLaunch(){}
void Menu::onEvent(sf::Event& Event){}
void Menu::onLoseFocus(){}
void Menu::onGainFocus(){}
void Menu::onExit(){}
MenuManager::MenuManager(sf::RenderWindow& Window):m_Window(Window),m_Input(Window),m_HasFocus(true){}
void MenuManager::run(Menu* Main) {
    pushMenu(Main);
    sf::Clock FrameClock;
    while(m_Window.isOpen()) {
        m_Input.Reset();
        m_StackChanged=false;
        sf::Event Event;
        while(m_Window.pollEvent(Event)) {
            if(Event.type==sf::Event::Closed) {
                while(m_MenuStack.size()) popMenu();
            }
            if(Event.type==sf::Event::LostFocus) {
                m_HasFocus=false;
                m_MenuStack[m_MenuStack.size()-1]->onLoseFocus();
            }
            if(Event.type==sf::Event::GainedFocus) {
                m_HasFocus=true;
                m_MenuStack[m_MenuStack.size()-1]->onGainFocus();
            }
            if(Event.type==sf::Event::Resized) {
                bool Limited=false;
                if(Event.size.width<550)
                    Event.size.width=550,
                    Limited=true;
                if(Event.size.height<150)
                    Event.size.height=150,
                    Limited=true;
                if(Limited)
                    m_Window.setSize({Event.size.width,Event.size.height});
                sf::View View({0,0,(float)Event.size.width,(float)Event.size.height});
                m_Window.setView(View);
                for(int i=0;i<m_MenuStack.size();i++) {
                    m_MenuStack[i]->createRender({Event.size.width,Event.size.height});
                    m_MenuStack[i]->createMenu({Event.size.width,Event.size.height});
                }
            }
            m_Input.Event(Event);
            if(m_MenuStack.size()) m_MenuStack[m_MenuStack.size()-1]->onEvent(Event);
            if(m_StackChanged) break;
        }
        if(!m_StackChanged) {
            m_Window.clear();
            sf::Time Delta=FrameClock.getElapsedTime();
            FrameClock.restart();
            for(int i=0;i<m_MenuStack.size();i++) {
                m_MenuStack[i]->updateTransition(Delta);
                if(m_MenuStack[i]->getExiting()&&m_MenuStack[i]->transitionIsDone()) {
                    m_MenuStack[i]->onExit();
                    delete m_MenuStack[i];
                    m_MenuStack.erase(m_MenuStack.begin()+i);
                    if(m_MenuStack.size()) m_MenuStack[i-1]->onGainFocus();
                    m_StackChanged=true;
                }
                else
                    m_MenuStack[i]->update(Delta,i==m_MenuStack.size()-1),
                    m_Window.draw(m_MenuStack[i]->getRender());
            }
            m_Window.display();
        }
        if(m_HasFocus==false) sf::sleep(sf::seconds(1));
    }
}
void MenuManager::pushMenu(Menu* Menu,MenuTransition* Transition) {
    m_MenuStack.push_back(Menu);
    Menu->onLaunch();
    Menu->createRender(m_Window.getSize(),Transition);
    Menu->createMenu(m_Window.getSize());
    Menu->onGainFocus();
    if(m_MenuStack.size()>1)m_MenuStack[m_MenuStack.size()-2]->onLoseFocus();
    m_StackChanged=true;
}
void MenuManager::popMenu(bool UseTransition) {
    m_MenuStack[m_MenuStack.size()-1]->exit();
}
AssetManager& MenuManager::getAssets(){return m_Assets;}
InputManager& MenuManager::getInput(){return m_Input;}
NetworkDiscovery& MenuManager::getDiscovery(){return m_Discovery;}
sf::RenderWindow& MenuManager::getWindow(){return m_Window;}
std::vector<Menu*>& MenuManager::getMenuStack(){return m_MenuStack;}
