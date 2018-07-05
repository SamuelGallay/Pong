#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "particles.hpp"

#if SAM_XCODE
#include "ResourcePath.hpp"
#endif

class Game
{
public:
    Game();
    void run();

private:
    //-- Les fonctions --//
    void restart();
    void update(sf::Time deltaTime);
    void processEvents();
    void paddlesInput(sf::Time deltaTime);
    void updateMessages();
    void render();
    
    //-- Les constantes --//
    const int tailleX;
    const int tailleY;
    const int tailleBordureRect;
    const int rayon;
    const int bordureBille;
    const float pi;

    //-- Les variables --//
    float paddleSpeed;
    float vitesseBille;
    float angle;
    bool enJeu;
    sf::Vector2f tailleRect;
    sf::Vector2i score;
    
    //-- Les Objets --//
    sf::RenderWindow window;
    sf::View vue;
    sf::Clock clock;
    ParticleSystem particles;
    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle2;
    sf::CircleShape cercle;
    sf::Text messageBienvenue;
    sf::Text message2;
    sf::Text message3;
    sf::Text blue;
    sf::Text red;
    sf::Music music;
    sf::SoundBuffer ballSoundBuffer;
    sf::Sound ballSound;
    sf::Image icon;
    sf::Font font;
    sf::VertexArray fond;
};

#endif
