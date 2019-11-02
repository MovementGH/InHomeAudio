#include "Filters.hpp"

bool AudioFilter::Filter(std::vector<sf::Int16> &Samples) {
    return true;
}

NoiseFilter::NoiseFilter(int QuietLevel):m_Quiet(QuietLevel){}
bool NoiseFilter::Filter(std::vector<sf::Int16> &Samples) {
    bool Noise=false;
    for(int i=0;i<Samples.size();i++) if(Samples[i]>m_Quiet||Samples[i]<-m_Quiet) Noise=true;
    return Noise;
}
