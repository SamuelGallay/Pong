#include "introState.hpp"

#include "gameState.hpp"

IntroState::IntroState( StateMachine& machine, sf::RenderWindow& window, bool replace )
: State{ machine, window, replace }
{
    std::cout << "IntroState Init" << std::endl;
    icon = machine.getResourceHolder().icon;
    m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
    messageBienvenue.setFont(font);
    messageBienvenue.setCharacterSize(40);
    messageBienvenue.setFillColor(sf::Color::White);
    messageBienvenue.setString("Intro : Pong de Samuel !!!");
    messageBienvenue.setPosition((window.getSize().x-messageBienvenue.getGlobalBounds().width)/2, window.getSize().y/3);
}

void IntroState::pause()
{
    std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume()
{
    std::cout << "IntroState Resume" << std::endl;
}

void IntroState::update()
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
            {
                switch( event.key.code )
                {
                    case sf::Keyboard::Space:
                        m_next = StateMachine::build<GameState>( m_machine, m_window, true );
                        break;
                        
                    case sf::Keyboard::Escape:
                        m_machine.quit();
                        break;
                        
                    default:
                        break;
                }
                break;
            }
                
            default:
                break;
        }
    }
    
}

void IntroState::draw()
{
    // Clear the previous drawing
    m_window.clear();
    m_window.setView(vue);
    m_window.setView(sf::View(sf::FloatRect(0, 0, m_window.getSize().x, m_window.getSize().y)));
    m_window.draw(fond);
    messageBienvenue.setPosition((m_window.getSize().x-messageBienvenue.getGlobalBounds().width)/2, m_window.getSize().y*3/8);
    m_window.draw(messageBienvenue);
    m_window.display();
}
