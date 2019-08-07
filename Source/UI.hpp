#ifndef UI_hpp
#define UI_hpp
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include <iostream>
class InputManager {
public:
    InputManager();
    
    void Event(sf::Event& Event);
    void Reset();
    
    bool isClicking();
    sf::Vector2i getMousePos();
    sf::Int16 getScrollSpeed();
private:
    bool m_IsClicking;
    int m_ScrollTime;
    sf::Vector2i m_MousePos;
    sf::Int16 m_ScrollSpeed;
};
class Button {
public:
    template <typename Entity> Button(InputManager& Input,Entity& Binder) : m_Input(Input) { Bind(Binder); }
    template <typename Entity> void Bind(Entity& Binder) { m_Area=Binder.getGlobalBounds();
        std::cout<<"Bound to "<<m_Area.left<<" "<<m_Area.width<<" "<<m_Area.top<<" "<<m_Area.height<<std::endl;
    };
    
    bool Hovering();
    bool Clicking();
    bool Clicked();
    
private:
    sf::FloatRect m_Area;
    bool m_IsClicked;
    
    InputManager& m_Input;
};


#endif /* UI_hpp */
