#include "Transitions.hpp"
namespace MenuTransitions {
    Grow::Grow(sf::Vector2f Center,float Speed):m_Center(Center),m_Speed(Speed),m_IsExiting(false){}
    void Grow::init(sf::Sprite& RenderSprite) {
        RenderSprite.setOrigin(m_Center);
        RenderSprite.setPosition(m_Center);
        RenderSprite.setScale(.05,.05);
    }
    void Grow::exit(sf::Sprite& RenderSprite) {
        m_IsExiting=true;
    }
    void Grow::update(sf::Time Delta,sf::Sprite& RenderSprite) {
        if(isDone(RenderSprite)==false) {
            if(m_IsExiting)
                RenderSprite.setScale(std::max(RenderSprite.getScale().x*(1-m_Speed),.05f),std::max(RenderSprite.getScale().x*(1-m_Speed),.05f));
            else RenderSprite.setScale(std::min(RenderSprite.getScale().x*(1+m_Speed),1.f),std::min(RenderSprite.getScale().x*(1+m_Speed),1.0f));
        }
    }
    bool Grow::isDone(sf::Sprite& RenderSprite) {
        return m_IsExiting?(RenderSprite.getScale().x<=.06f):(RenderSprite.getScale().x>=1);
    }
}
