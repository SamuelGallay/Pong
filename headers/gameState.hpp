#include <memory>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "stateMachine.hpp"

#include "particles.hpp"

class GameState : public State
{
public:
    GameState( StateMachine& game, sf::RenderWindow& window, bool replace = true );
    
    void pause();
    void resume();
    
    void update();
    void draw();
    
private:
    //-- Les fonctions --//
    void restart();
    void update(sf::Time deltaTime);
    void processEvents();
    void paddlesInput(sf::Time deltaTime);
    void updateMessages();
    
    //-- Les constantes --//
    const int tailleX;
    const int tailleY;
    const int tailleBordureRect;
    const int rayon;
    const int bordureBille;
    const float pi;
    
    //-- Les variables --//
    bool enPause;
    float paddleSpeed;
    float vitesseBille;
    float angle;
    sf::Vector2f tailleRect;
    sf::Vector2i score;
    
    //-- Les Objets --//
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
};
