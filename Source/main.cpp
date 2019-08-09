#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <SFML/Main.hpp>
#endif
#endif
#include "Transitions.hpp"
#include "Menus/TitleBar.hpp"
#include "Menus/MainMenu.hpp"

int main() {
    sf::RenderWindow Window;
    Window.create(isMobile()?sf::VideoMode::getDesktopMode():sf::VideoMode(1280,720),"In Home Audio");
    Window.setVerticalSyncEnabled(true);
    MenuManager Manager(Window);
    Manager.pushMenu(new Menus::TitleBar(&Manager));
    Manager.pushMenu(new Menus::MainMenu(&Manager));
    Manager.run();
    return EXIT_SUCCESS;
    
}
