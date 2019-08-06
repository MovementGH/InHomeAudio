//
//  main.cpp
//  In-Home Audio
//
//  Created by Mayo Furgerson on 8/6/19.
//  Copyright © 2019 WimMa Games. All rights reserved.
//

#include <iostream>
#include "NetworkDiscovery.hpp"

int main(int argc, const char * argv[]) {
    std::cout<<"Start"<<std::endl;
    
    NetworkDiscovery Discoverer(true);
    
    sf::sleep(sf::seconds(60));
}
