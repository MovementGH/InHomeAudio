#include "UI.hpp"
InputManager::InputManager() : m_IsClicking(false), m_MousePos(0,0), m_ScrollSpeed(0), m_ScrollTime(0) {
    
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
            m_ScrollSpeed=Event.mouseWheel.delta;
    }
    else {
        if(Event.type==sf::Event::TouchBegan)
            m_ScrollTime=0;
        if(Event.type==sf::Event::TouchEnded) {
            if(m_ScrollTime<5)
                m_MousePos={Event.touch.x,Event.touch.y},
                m_IsClicking=true;
            else
                m_MousePos={-1,-1};
        }
        if(Event.type==sf::Event::TouchMoved)
            m_ScrollSpeed=Event.touch.y-m_MousePos.y,
            m_ScrollTime++,
            m_MousePos={Event.touch.x,Event.touch.y};
    }
}
void InputManager::Reset() {
    m_ScrollSpeed=0;
    if(isMobile()) m_IsClicking=false;
}
bool InputManager::isClicking() {
    return m_IsClicking;
}
sf::Vector2i InputManager::getMousePos() {
    return m_MousePos;
}
sf::Int16 InputManager::getScrollSpeed() {
    return m_ScrollSpeed;
}
bool Button::Hovering() {
    sf::Vector2i MousePos=m_Input.getMousePos();
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
