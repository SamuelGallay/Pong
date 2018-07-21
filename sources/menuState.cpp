#include "menuState.hpp"

MenuState::MenuState( StateMachine& machine, sf::RenderWindow& window, bool replace )
: State{ machine, window, replace }
{
	std::cout << "MenuState Init" << std::endl;
    fond.setPrimitiveType(sf::Quads);
    fond.resize(4);
    fond[0].position = sf::Vector2f(0, 0);
    fond[1].position = sf::Vector2f(m_window.getSize().x, 0);
    fond[2].position = sf::Vector2f(m_window.getSize().x, m_window.getSize().y);
    fond[3].position = sf::Vector2f(0, m_window.getSize().y);
    fond[0].color = sf::Color::Blue;
    fond[1].color = sf::Color::Red;
    fond[2].color = sf::Color::Red;
    fond[3].color = sf::Color::Blue;
    
    vue = window.getDefaultView();
    vue.setCenter(400, 300);
    font = machine.getResourceHolder().font;
    message.setFont(font);
    message.setCharacterSize(50);
    message.setFillColor(sf::Color::White);
    message.setString("Menu :");
    message.setPosition((window.getSize().x-message.getGlobalBounds().width)/2, window.getSize().y/3);
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MenuState::update()
{
	sf::Event event;

	while( m_window.pollEvent( event ) )
	{
		switch( event.type )
		{
			case sf::Event::Closed:
				m_machine.quit();
				break;
                
            case sf::Event::Resized:
                resized();
                break;

			case sf::Event::KeyPressed:
				switch( event.key.code )
				{
                    case sf::Keyboard::Space:
						m_machine.lastState();
						break;
                        
                    case sf::Keyboard::Escape:
                        m_machine.quit();
                        break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}

void MenuState::draw()
{
    m_window.clear();
    m_window.setView(vue);
    m_window.setView(sf::View(sf::FloatRect(0, 0, m_window.getSize().x, m_window.getSize().y)));
    m_window.draw(fond);
    message.setPosition((m_window.getSize().x-message.getGlobalBounds().width)/2, m_window.getSize().y*2/8);
    m_window.draw(message);
    m_window.display();
}
