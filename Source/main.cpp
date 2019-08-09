#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <SFML/Main.hpp>
#endif
#endif
#include "Menu.hpp"
#include "Menus/Loading.hpp"
#include "Menus/TitleBar.hpp"

int main() {
    sf::RenderWindow Window;
    Window.create(isMobile()?sf::VideoMode::getDesktopMode():sf::VideoMode(1280,720),"In Home Audio");
    if(isMobile()==false) Window.setVerticalSyncEnabled(true);
    MenuManager Manager(Window);
    Manager.run(isMobile()?((Menu*)new Menus::LoadingMenu(&Manager)):((Menu*)new Menus::TitleBar(&Manager)));
    return EXIT_SUCCESS;
    
}
