#include "UI.hpp"
InputManager::InputManager(sf::RenderWindow& Window) : m_IsClicking(false), m_MousePos(0,0), m_ScrollSpeed(0), m_ScrollTime(0), m_ResetMouse(false), m_Window(Window) {
    
}
void InputManager::Event(sf::Event& Event) {
    if(isMobile()==false) {
        if(Event.type==sf::Event::MouseButtonPressed&&Event.mouseButton.button==sf::Mouse::Left)
            m_IsClicking=true;
        if(Event.type==sf::Event::MouseButtonReleased&&Event.mouseButton.button==sf::Mouse::Left)
            m_IsClicking=false;
        if(Event.type==sf::Event::MouseMoved)
            m_MousePos={Event.mouseMove.x,Event.mouseMove.y};
        if(Event.type==sf::Event::MouseWheelMoved)
            m_ScrollSpeed=Event.mouseWheel.delta*3;
    }
    else {
        if(Event.type==sf::Event::TouchEnded&&Event.touch.finger==0) {
            if(m_ScrollTime<5)
                m_MousePos={Event.touch.x,Event.touch.y},
                m_IsClicking=true;
            else m_MousePos={-1,-1};
            m_ScrollTime=0;
        }
        if(Event.type==sf::Event::TouchMoved&&Event.touch.finger==0)
            m_ScrollTime++,
            m_ScrollSpeed=m_ScrollTime>1?(Event.touch.y-m_MousePos.y):0,
            m_MousePos={Event.touch.x,Event.touch.y};
    }
}
void InputManager::Reset() {
    if(isMobile()) m_ScrollSpeed*=.95;
    else m_ScrollSpeed=0;
    if(m_ResetMouse)
        m_ResetMouse=false,
        m_MousePos={-1,-1};
    if(isMobile()&&m_IsClicking)
        m_ResetMouse=true,
        m_IsClicking=false;
}
bool InputManager::isClicking() {
    return m_IsClicking;
}
sf::Vector2i InputManager::getMousePos() {
    return m_MousePos;
}
float InputManager::getScrollSpeed() {
    return -m_ScrollSpeed;
}
sf::RenderWindow& InputManager::getWindow(){return m_Window;}
AssetBase::~AssetBase(){}
AssetBase::AssetBase(std::string Filename):m_Filename(Filename){}
Button::Button(InputManager& Input) : m_Input(Input),m_IsClicked(false){}
Button::Button(Button& Button) : m_Input(Button.m_Input) {
    m_Area=Button.m_Area;
    m_IsClicked=Button.m_IsClicked;
}
bool Button::Hovering(sf::RenderTarget* Renderer) {
    if(Renderer==nullptr) Renderer=&m_Input.getWindow();
    sf::Vector2f MousePos=Renderer->mapPixelToCoords(m_Input.getMousePos());
    return MousePos.x>m_Area.left&&MousePos.x<m_Area.left+m_Area.width&&MousePos.y>m_Area.top&&MousePos.y<m_Area.top+m_Area.height;
}
bool Button::Clicking() {
    return Hovering()&&m_Input.isClicking();
}
bool Button::Clicked() {
    bool Result=Hovering()&&(m_Input.isClicking()==false)&&m_IsClicked==true;
    m_IsClicked=m_Input.isClicking();
    return Result;
}
ScrollArea::ScrollArea():m_Scroll(0){}
void ScrollArea::setArea(sf::FloatRect Area,sf::Vector2u WindowSize) {
    m_Area=Area;
    m_View.reset({10000,0,Area.width,Area.height});
    m_View.setViewport({(float)Area.left/WindowSize.x,(float)Area.top/WindowSize.y,(float)Area.width/WindowSize.x,(float)Area.height/WindowSize.y});
}
void ScrollArea::setHeight(float Height) {
    m_EndPos=std::max(Height,m_Area.height);
}
void ScrollArea::update(InputManager& Input) {
    float Delta=Input.getScrollSpeed();
    if(m_Scroll+Delta>0&&m_Scroll+Delta<m_EndPos-m_Area.height)
        m_Scroll+=Delta;
    else if(m_Scroll+Delta<=0)
        m_Scroll=0;
    else if(m_Scroll+Delta>m_EndPos-m_Area.height)
        m_Scroll=m_EndPos-m_Area.height;
    m_View.reset({10000,m_Scroll,m_Area.width,m_Area.height});
}
sf::View& ScrollArea::getView() {
    return m_View;
}
