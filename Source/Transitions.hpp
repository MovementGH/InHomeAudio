#ifndef Transitions_hpp
#define Transitions_hpp
#include "Menu.hpp"
namespace MenuTransitions {
    class Grow : public MenuTransition {
    public:
        Grow(sf::Vector2f Center,float Speed);
        virtual void init(sf::Sprite& RenderSprite)override;
        virtual void exit(sf::Sprite& RenderSprite)override;
        virtual void update(sf::Time Delta,sf::Sprite& RenderSprite)override;
        virtual bool isDone(sf::Sprite& RenderSprite)override;
    protected:
        sf::Vector2f m_Center;
        float m_Speed;
    };
}
#endif /* Transitions_hpp */
