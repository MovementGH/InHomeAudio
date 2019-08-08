#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <SFML/Main.hpp>
#endif
#endif
#include "Menu.hpp"
#include "Loading.hpp"

int main() {
    sf::RenderWindow Window;
    Window.create(sf::VideoMode::getDesktopMode(),"In Home Audio");
    Window.setVerticalSyncEnabled(true);
    MenuManager Manager(Window);
    Manager.run(new Menus::LoadingMenu(&Manager));
    
    return EXIT_SUCCESS;
    
//    InputManager Input;
//
//    sf::Font Font;
//    Font.loadFromFile(resourcePath()+"sansation.ttf");
//    sf::Text Text("",Font,64);
//
//    while(Window.isOpen()) {
//        Input.Reset();
//        sf::Event Event;
//        while(Window.pollEvent(Event)) {
//            if(Event.type==sf::Event::Closed)
//                Window.close();
//            Input.Event(Event);
//        }
//        Text.setString("Mouse: "+std::to_string(Input.getMousePos().x)+":"+std::to_string(Input.getMousePos().y)+"\nClick: "+(Input.isClicking()?"true":"false")+"\nScroll: "+std::to_string(Input.getScrollSpeed()));
//        Window.clear();
//        Window.draw(Text);
//        Window.display();
//    }
//    DualDeviceStreamerStreamer Streamer;
//    Streamer.setCodec<OpusCodec>(new OpusCodec(32000));
//    Streamer.Connect("192.168.1.143");
//    Streamer.setBufferSize(sf::seconds(.2));
//    sf::sleep(sf::seconds(60));
//    while(true) {
//        std::vector<NetworkDevice> Devices=Discoverer.getDevices();
//        for(int i=0;i<Devices.size();i++)
//            std::cout<<(std::string)Devices[i].name<<" from "<<Devices[i].ip<<" on "<<getPlatformName(Devices[i].platform)<<" at "<<Devices[i].lastSeen<<std::endl;
//        std::cout<<std::endl<<std::endl;
//        sf::sleep(sf::seconds(1));
//    }
    
}
