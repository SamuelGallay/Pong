#include "state.hpp"

State::State( StateMachine& machine, sf::RenderWindow &window, bool replace )
: m_machine{ machine }
, m_window{ window }
, m_replacing{ replace }
{

}

std::unique_ptr<State> State::next()
{
	return std::move( m_next );
}

bool State::isReplacing()
{
	return m_replacing;
}

void State::resized()
{
    float zoom = 1.f;
    if(static_cast<float>(m_window.getSize().x) / static_cast<float>(m_window.getSize().y) > static_cast<float>(800) / static_cast<float>(600)){
        zoom = static_cast<float>(m_window.getSize().y) / static_cast<float>(600);
    }
    else{
        zoom = static_cast<float>(m_window.getSize().x) / static_cast<float>(800);
    }
    vue.setViewport(sf::FloatRect((1-zoom*static_cast<float>(800)/static_cast<float>(m_window.getSize().x))/2, (1-zoom*static_cast<float>(600)/static_cast<float>(m_window.getSize().y))/2, zoom*static_cast<float>(800)/static_cast<float>(m_window.getSize().x), zoom*static_cast<float>(600)/static_cast<float>(m_window.getSize().y)));
    m_window.setView(vue);
    fond[0].position = sf::Vector2f(0, 0);
    fond[1].position = sf::Vector2f(m_window.getSize().x, 0);
    fond[2].position = sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
    fond[3].position = sf::Vector2f(0, m_window.getSize().y);
}
