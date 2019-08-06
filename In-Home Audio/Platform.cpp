//
//  Platform.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include "Platform.hpp"

#ifdef __APPLE__
#ifdef MacOS
#define PLATFORM Platform::Mac
//Mac
#elif iOS
#define MOBILE
#define PLATFORM Platform::iOS
//iOS
#else
# error Invalid platform
#endif
#elif __linux__
#define PLATFORM Platform::Linux
//Linux
#elif _WIN32
#define PLATFORM Plaform::Windows
//Windows
#else
# error Invalid platform
#endif

#ifdef MOBILE
#define Mobile true
//Mobile
#else
#define Mobile false
//Desktop
#endif

Platform getPlatform() {
    return PLATFORM;
}
