#ifndef UI_hpp
#define UI_hpp
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
class InputManager {
public:
    InputManager(sf::RenderWindow& Window);
    
    void Event(sf::Event& Event);
    void Reset();
    
    bool isClicking();
    sf::Vector2i getMousePos();
    sf::Int16 getScrollSpeed();
private:
    bool m_IsClicking,m_WasScrolling;
    sf::Vector2i m_MousePos;
    sf::Int16 m_ScrollSpeed;
    
    sf::RenderWindow& m_Window;
};
class Button {
public:
    template <typename Entity> Button(Entity& Binder);
    template <typename Entity> void Bind(Entity& Binder);
    
    bool Hovering(InputManager& Input);
    bool Clicking(InputManager& Input);
    bool Clicked(InputManager& Input);
    
private:
    sf::FloatRect Area;
    bool IsClicked;
};


#endif /* UI_hpp */
