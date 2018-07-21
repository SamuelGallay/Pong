#include "application.hpp"


void Application::run()
{
    // Create render window
    m_window.create(sf::VideoMode(800, 600, 32), "Pong");
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);

    
    // Initialize the engine
    m_machine.run( StateMachine::build<IntroState>( m_machine, m_window, true ) );
    
    // Main loop
    while( m_machine.running() )
    {
        m_machine.nextState();
        m_machine.update();
        m_machine.draw();
    }
    
    // Leaving the scope of 'Application' will cleanup the engine
}

