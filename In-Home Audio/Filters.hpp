#ifndef Filters_hpp
#define Filters_hpp
#include <vector>
#include <SFML/System.hpp>

class AudioFilter {
public:
    bool Filter(std::vector<sf::Int16>& Samples);
};

#endif /* Filters_hpp */
