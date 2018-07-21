#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "stateMachine.hpp"

class IntroState : public State
{
public:
	IntroState( StateMachine& game, sf::RenderWindow& window, bool replace = true );

	void pause();
	void resume();

	void update();
	void draw();

private:
    sf::Font font;
    sf::Text messageBienvenue;
    sf::Image icon;
};

#endif // INTROSTATE_HPP
