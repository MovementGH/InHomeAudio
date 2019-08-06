//
//  Platform.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp
enum Platform {
    Windows = 0,
    Mac = 1,
    Linux = 2,
    iOS = 3
};

Platform getPlatform();
#endif /* Platform_hpp */
