#include "Transitions.hpp"
namespace MenuTransitions {
    Grow::Grow(sf::Vector2f Center,float Speed):m_Center(Center),m_Speed(Speed){}
    void Grow::enter(sf::Sprite& RenderSprite) {
        RenderSprite.setOrigin(m_Center);
        RenderSprite.setPosition(m_Center);
        RenderSprite.setScale(.05,.05);
        m_IsExit=false;
    }
    void Grow::exit(sf::Sprite& RenderSprite) {
        RenderSprite.setOrigin(m_Center);
        RenderSprite.setPosition(m_Center);
        RenderSprite.setScale(1,1);
        m_IsExit=true;
    }
    void Grow::update(sf::Time Delta,sf::Sprite& RenderSprite) {
        if(isDone(RenderSprite)==false) {
            if(m_IsExit)
                RenderSprite.setScale(std::max(RenderSprite.getScale().x*(1-m_Speed),.05f),std::max(RenderSprite.getScale().x*(1-m_Speed),.05f));
            else RenderSprite.setScale(std::min(RenderSprite.getScale().x*(1+m_Speed),1.f),std::min(RenderSprite.getScale().x*(1+m_Speed),1.0f));
        }
    }
    bool Grow::isDone(sf::Sprite& RenderSprite) {
        return m_IsExit?(RenderSprite.getScale().x<=.06f):(RenderSprite.getScale().x>=1);
    }
    
    Slide::Slide(Slide::Direction Origin,float Speed):m_Speed(Speed*Origin){}
    void Slide::enter(sf::Sprite& RenderSprite) {
        RenderSprite.setPosition((int)RenderSprite.getTexture()->getSize().x*(m_Speed>0?-1:1),0);
        m_IsExit=false;
    }
    void Slide::exit(sf::Sprite& RenderSprite) {
        RenderSprite.setPosition(0,0);
        m_IsExit=true;
    }
    void Slide::update(sf::Time Delta,sf::Sprite& RenderSprite) {
        if(isDone(RenderSprite)==false) {
            if(m_IsExit) {
                RenderSprite.move(-m_Speed*(float)RenderSprite.getTexture()->getSize().x,0);
                if(RenderSprite.getPosition().x<(int)RenderSprite.getTexture()->getSize().x*-1)
                    RenderSprite.setPosition((int)RenderSprite.getTexture()->getSize().x*-1,0);
                if(RenderSprite.getPosition().x>RenderSprite.getTexture()->getSize().x)
                    RenderSprite.setPosition(RenderSprite.getTexture()->getSize().x,0);
            }
            else {
                RenderSprite.move(m_Speed*(float)RenderSprite.getTexture()->getSize().x,0);
                if((RenderSprite.getPosition().x>0&&m_Speed>0)||(RenderSprite.getPosition().x<0&&m_Speed<0))
                    RenderSprite.setPosition(0,0);
            }
        }
    }
    bool Slide::isDone(sf::Sprite& RenderSprite) {
        return RenderSprite.getPosition().x==(m_IsExit?((int)RenderSprite.getTexture()->getSize().x*(m_Speed>0?-1:1)):0);
    }
}
