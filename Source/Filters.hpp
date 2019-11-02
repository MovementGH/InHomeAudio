#ifndef Filters_hpp
#define Filters_hpp
#include <vector>
#include <SFML/System.hpp>

class AudioFilter {
public:
    bool Filter(std::vector<sf::Int16>& Samples);
};

class NoiseFilter {
public:
    NoiseFilter(int QuietLevel=0);
    bool Filter(std::vector<sf::Int16>& Samples);
protected:
    int m_QuietLevel;
};

#endif /* Filters_hpp */
