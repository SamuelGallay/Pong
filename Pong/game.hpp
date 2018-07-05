#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#if SAM_XCODE
#include "ResourcePath.hpp"
#endif
#include "particles.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void restart();
    bool update(float deltaTime);
    void processEvents();
    
    const int tailleX;
    const int tailleY;
    const int tailleBordureRect;
    const int rayon;
    const int bordureBille;
    const float pi;

    float paddleSpeed;
    float vitesseBille;
    float angle;
    sf::Vector2f tailleRect;
    
    sf::View vue;
    sf::RenderWindow window;
    ParticleSystem particles;
    sf::Clock clock;
    bool enJeu;

    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle2;
    sf::CircleShape cercle;
    sf::Text messageBienvenue;
    sf::Text message2;
    sf::Text message3;
    sf::Text blue;
    sf::Text red;
    sf::Vector2i score;
    sf::Music music;
    sf::SoundBuffer ballSoundBuffer;
    sf::Sound ballSound;
    sf::Image icon;
    sf::Font font;
    sf::VertexArray fond;
    
};

#endif
