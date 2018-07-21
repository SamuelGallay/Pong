#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include "SFML/Graphics.hpp"

class StateMachine;

class State
{
public:
	State( StateMachine& machine, sf::RenderWindow& window, bool replace = true );
	virtual ~State() = default;


    State ( const State& ) = delete;
    State& operator= ( const State& ) = delete;
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;
    
    void resized();

	std::unique_ptr<State> next();

	bool isReplacing();

protected:
    StateMachine& m_machine;
    sf::RenderWindow& m_window;

	bool m_replacing;

	std::unique_ptr<State> m_next;
    
    sf::VertexArray fond;
    sf::View vue;
};

#endif // STATE_HPP
