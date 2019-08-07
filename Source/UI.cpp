#include "UI.hpp"
InputManager::InputManager(sf::RenderWindow& Window) : m_Window(Window), m_IsClicking(false), m_MousePos(0,0), m_ScrollSpeed(0) {
    
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
            m_WasScrolling=false;
        if(Event.type==sf::Event::TouchEnded)
            if(m_WasScrolling==false)
                m_IsClicking=true;
        if(Event.type==sf::Event::TouchMoved)
            m_WasScrolling=true,
            m_ScrollSpeed=Event.touch.y-m_MousePos.y,
            m_MousePos={Event.touch.x,Event.touch.y};
    }
}
void InputManager::Reset() {
    m_ScrollSpeed=0;
    if(isMobile())
        m_IsClicking=false;
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
bool Button::Hovering(InputManager& Input) {
    sf::Vector2i MousePos=Input.getMousePos();
    return MousePos.x>Area.left&&MousePos.x<Area.left+Area.width&&MousePos.y>Area.top&&MousePos.y<Area.top+Area.height;
}
bool Button::Clicking(InputManager& Input) {
    return Hovering(Input)&&Input.isClicking();
}
bool Button::Clicked(InputManager& Input) {
    bool Result=Hovering(Input)&&(Input.isClicking()==false)&&IsClicked==true;
    IsClicked=Input.isClicking();
    return Result;
}
