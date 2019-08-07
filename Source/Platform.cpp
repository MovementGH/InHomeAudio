#include "Platform.hpp"

#ifdef __APPLE__
#ifdef MacOS
//Mac
#include <unistd.h>
#define PLATFORM Platform::Mac
std::string getComputerName() {
    char name[50];
    if(gethostname(name,50)) return "Unknown";
    return name;
}
//End Mac
#elif IOS
//iOS
#define MOBILE
#define PLATFORM Platform::iOS
std::string getComputerName() {
    return "Unknown";
}
//End iOS
#else
# error Invalid platform
#endif
#elif __linux__
//Linux
#include <unistd.h>
#define PLATFORM Platform::Linux
std::string getComputerName() {
    char name[50];
    if(gethostname(name,50)) return "Unknown";
    return name;
}
//End Linux
#elif _WIN32
//Windows
#define PLATFORM Plaform::Windows
//End Windows
#else
# error Invalid platform
#endif

#ifdef MOBILE
//Mobile
#define Mobile true
//End Mobile
#else
//Desktop
#define Mobile false
//End Desktop
#endif

Platform getPlatform() {
    return PLATFORM;
}
bool isMobile() {
    return Mobile;
}
std::string getPlatformName(Platform platform) {
    std::string PlatformNames[4]={"Windows","Mac","Linux","iOS"};
    return PlatformNames[platform];
}
