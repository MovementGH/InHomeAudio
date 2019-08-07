#ifndef Platform_hpp
#define Platform_hpp
#include <string>

enum Platform {
    Windows = 0,
    Mac = 1,
    Linux = 2,
    iOS = 3
};

std::string getComputerName();
std::string getPlatformName(Platform platform);
Platform getPlatform();
bool isMobile();
#endif /* Platform_hpp */
