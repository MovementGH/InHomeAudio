//
//  Filters.hpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#ifndef Filters_hpp
#define Filters_hpp
#include <vector>
#include <SFML/System.hpp>

class AudioFilter {
public:
    bool Filter(std::vector<sf::Int16>& Samples);
};

#endif /* Filters_hpp */
