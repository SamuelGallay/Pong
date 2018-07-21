#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "stateMachine.hpp"

class MenuState : public State
{
public:
	MenuState( StateMachine& machine, sf::RenderWindow& window, bool replace = true );

	void pause();
	void resume();

	void update();
	void draw();

private:
    sf::Font font;
    sf::Text message;
};

#endif // MENUSTATE_HPP
