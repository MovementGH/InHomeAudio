//
//  Platform.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp
#include <string>

enum Platform {
    Windows = 0,
    Mac = 1,
    Linux = 2,
    iOS = 3
};

std::string getPlatformName(Platform platform);
Platform getPlatform();
#endif /* Platform_hpp */
