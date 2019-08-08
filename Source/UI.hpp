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
    float getScrollSpeed();
private:
    bool m_IsClicking;
    int m_ScrollTime;
    sf::Vector2i m_MousePos;
    float m_ScrollSpeed;
};
class AssetBase{
public:
    virtual ~AssetBase();
    AssetBase(std::string Filename);
    virtual void* getAsset()=0;
    std::string m_Filename;
};

template <typename AssetType>
class Asset : public AssetBase {
public:
    virtual ~Asset(){}
    Asset(std::string Filename) : AssetBase(Filename) {
        m_Asset.loadFromFile(Filename);
    }
    virtual void* getAsset() override { return &m_Asset; }
    AssetType m_Asset;
};
class AssetManager {
public:
    template<typename AssetType> AssetType& getAsset(std::string Filename) {
        for(int i=0;i<m_Assets.size();i++)
            if(m_Assets[i]->m_Filename==Filename)
                return *((AssetType*)m_Assets[i]->getAsset());
        m_Assets.emplace_back(new Asset<AssetType>(Filename));
        return *((AssetType*)m_Assets[m_Assets.size()-1]->getAsset());
    }
protected:
    std::vector<std::unique_ptr<AssetBase>> m_Assets;
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
class ScrollArea {
public:
    ScrollArea();
    
    void setArea(sf::FloatRect Area,sf::Vector2u WindowSize);
    void setHeight(float Height);
    void update(InputManager& Input);
    
    sf::View& getView();
protected:
    sf::View m_View;
    sf::FloatRect m_Area;
    float m_EndPos;
    float m_Scroll;
};



#endif /* UI_hpp */
