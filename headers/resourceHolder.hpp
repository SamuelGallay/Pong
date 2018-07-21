#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct ResourceHolder {
    sf::Font font;
    sf::SoundBuffer ballSoundBuffer;
    sf::Image icon;
    sf::Music music;
    
    ResourceHolder();
};


#endif
