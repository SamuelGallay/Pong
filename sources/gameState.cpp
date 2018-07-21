#include "gameState.hpp"

#include "menuState.hpp"

GameState::GameState( StateMachine& machine, sf::RenderWindow& window, bool replace )
: State{ machine, window, replace }, particles(1000), tailleX(800), tailleY(600), tailleBordureRect(4), rayon(15), bordureBille(3), pi(3.141593)
{
    std::cout << "PlayState Init" << std::endl;
    //-- Loading --//
    ballSoundBuffer = machine.getResourceHolder().ballSoundBuffer;
    ballSound.setBuffer(ballSoundBuffer);
    font = machine.getResourceHolder().font;
    //-- Vue --//
    vue = window.getDefaultView();
    vue.setCenter(400, 300);
    window.setView(vue);
    
    //-- Particles --//
    particles.resize(window.getSize().x * 5);
    
    //-- Mesures --//
    tailleRect.x = tailleX/25;
    tailleRect.y = tailleY/4;
    paddleSpeed = 550.f;
    vitesseBille = 350.f;
    angle = 3*pi/4;
    
    //-- Paddle Gauche --//
    rectangle.setSize(tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f);
    rectangle.setOrigin((tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f)/2.f);
    rectangle.setOutlineThickness(tailleBordureRect);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setPosition(tailleX/16, tailleY/2);
    rectangle.setFillColor(sf::Color::Transparent);
    
    //-- Paddle Droit --//
    rectangle2.setSize(tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f);
    rectangle2.setOrigin((tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f)/2.f);
    rectangle2.setOutlineThickness(tailleBordureRect);
    rectangle2.setOutlineColor(sf::Color::White);
    rectangle2.setPosition(tailleX-tailleX/16, tailleY/2);
    rectangle2.setFillColor(sf::Color::Transparent);
    
    //-- Balle --//
    cercle.setRadius(rayon - bordureBille);
    cercle.setOrigin(sf::Vector2f(rayon - bordureBille, rayon - bordureBille));
    cercle.setOutlineThickness(bordureBille);
    cercle.setOutlineColor(sf::Color::White);
    cercle.setPosition(tailleX/2, tailleY/2);
    cercle.setFillColor(sf::Color(170, 0, 170));
    cercle.setPointCount(30);
    
    //Message 3
    message3.setFont(font);
    message3.setCharacterSize(50);
    message3.setFillColor(sf::Color::White);
    message3.setString("");
    
    //Message Bleu
    blue.setFont(font);
    blue.setCharacterSize(50);
    blue.setFillColor(sf::Color::White);
    blue.setString("0");
    
    //Message Rouge
    red.setFont(font);
    red.setCharacterSize(50);
    red.setFillColor(sf::Color::White);
    red.setString("0");
    
    //Dégradé de fond
    fond.setPrimitiveType(sf::Quads);
    fond.resize(4);
    fond[0].position = sf::Vector2f(0, 0);
    fond[1].position = sf::Vector2f(tailleX, 0);
    fond[2].position = sf::Vector2f(tailleX, tailleY);
    fond[3].position = sf::Vector2f(0, tailleY);
    fond[0].color = sf::Color::Blue;
    fond[1].color = sf::Color::Red;
    fond[2].color = sf::Color::Red;
    fond[3].color = sf::Color::Blue;
    
    restart();
}

void GameState::pause()
{
    std::cout << "PlayState Pause" << std::endl;
}

void GameState::resume()
{
    std::cout << "PlayState Resume" << std::endl;
    enPause = true;
    clock.restart();
}

void GameState::update()
{
    processEvents();
    sf::Time deltaTime = clock.restart();
    paddlesInput(deltaTime);
    update(deltaTime);
    updateMessages();
}

void GameState::draw()
{
    m_window.clear(sf::Color::Black);
    
    m_window.setView(sf::View(sf::FloatRect(0, 0, m_window.getSize().x, m_window.getSize().y)));
    m_window.draw(fond);
    m_window.draw(blue);
    m_window.draw(red);
    m_window.draw(message3);

    m_window.setView(vue);
    m_window.draw(rectangle);
    m_window.draw(rectangle2);
    m_window.draw(particles);
    m_window.draw(cercle);
    
    m_window.display();
}

void GameState::restart()
{
    resized();
    paddleSpeed = tailleY;
    vitesseBille = tailleX/2;
    angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * pi;
    if(angle > pi/2){
        angle += pi/2;
    }
    angle += 3*pi/4;
    
    rectangle.setPosition(tailleX/16, tailleY/2);
    rectangle2.setPosition(tailleX-tailleX/16, tailleY/2);
    cercle.setPosition(tailleX/2, tailleY/2);
    
    enPause = true;
}

void GameState::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if ( (event.type == sf::Event::Closed) || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) ) )
        {
            m_next = StateMachine::build<MenuState>( m_machine, m_window, false );
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            if(!enPause){
                enPause = true;
            }
            else{
                enPause = false;
            }
        }
        
        if (event.type == sf::Event::Resized)
        {
            resized();
            particles.resize(m_window.getSize().x * 5);
            enPause = true;
        }
    }
}

void GameState::updateMessages()
{
    message3.setString(std::to_string(static_cast<int>(vitesseBille/40)));
    message3.setPosition((m_window.getSize().x-message3.getGlobalBounds().width)/2, m_window.getSize().y*0/8);
    blue.setPosition(m_window.getSize().x/4 - blue.getGlobalBounds().width/2, m_window.getSize().y/2 - blue.getGlobalBounds().height/2);
    red.setPosition(m_window.getSize().x*3/4 - red.getGlobalBounds().width/2, m_window.getSize().y/2 - red.getGlobalBounds().height/2);
}

void GameState::update(sf::Time deltaTime)
{
    if(!enPause)
    cercle.move(std::cos(angle) * vitesseBille * deltaTime.asSeconds(), std::sin(angle) * vitesseBille * deltaTime.asSeconds());
    
    
    if (cercle.getPosition().x - rayon < rectangle.getPosition().x + tailleRect.x / 2 &&
        cercle.getPosition().x - rayon > rectangle.getPosition().x - tailleRect.x / 2 &&
        cercle.getPosition().y + rayon >= rectangle.getPosition().y - tailleRect.y / 2 &&
        cercle.getPosition().y - rayon <= rectangle.getPosition().y + tailleRect.y / 2)
    {
        ballSound.play();
        if (cercle.getPosition().y > rectangle.getPosition().y)
            angle = pi - angle + (std::rand() % 20) * pi / 180;
        else
            angle = pi - angle - (std::rand() % 20) * pi / 180;
        
        cercle.setPosition(rectangle.getPosition().x + rayon + tailleRect.x / 2 + 0.1f, cercle.getPosition().y);
        vitesseBille *= 1.03f;
        paddleSpeed *= 1.04f;
    }
    
    if (cercle.getPosition().x + rayon > rectangle2.getPosition().x - tailleRect.x / 2 &&
        cercle.getPosition().x + rayon < rectangle2.getPosition().x + tailleRect.x / 2 &&
        cercle.getPosition().y + rayon >= rectangle2.getPosition().y - tailleRect.y / 2 &&
        cercle.getPosition().y - rayon <= rectangle2.getPosition().y + tailleRect.y / 2)
    {
        ballSound.play();
        if (cercle.getPosition().y > rectangle2.getPosition().y)
            angle = pi - angle + (std::rand() % 20) * pi / 180;
        else
            angle = pi - angle - (std::rand() % 20) * pi / 180;
        
        cercle.setPosition(rectangle2.getPosition().x - rayon - tailleRect.x / 2 - 0.1f, cercle.getPosition().y);
        vitesseBille *= 1.03f;
        paddleSpeed *= 1.04f;
    }
    
    
    if(cercle.getPosition().x - rayon < 0.f){
        messageBienvenue.setString("Rouge Gagne !!!");
        messageBienvenue.setCharacterSize(60);
        message2.setString("Echap pour quitter...");
        score.y++;
        red.setString(std::to_string(score.y));
        restart();
        //m_next = StateMachine::build<MenuState>( m_machine, m_window, false );
    }
    if(cercle.getPosition().x + rayon > tailleX){
        messageBienvenue.setString("Bleu Gagne !!!");
        messageBienvenue.setCharacterSize(60);
        message2.setString("Echap pour quitter...");
        score.x++;
        blue.setString(std::to_string(score.x));
        restart();
        //m_next = StateMachine::build<MenuState>( m_machine, m_window, false );
    }
    
    if(cercle.getPosition().y - rayon <= 0.f){
        ballSound.play();
        angle = -angle;
        cercle.setPosition(cercle.getPosition().x, rayon + 0.1f);
        vitesseBille *= 1.03f;
    }
    
    if(cercle.getPosition().y + rayon > tailleY){
        ballSound.play();
        angle = -angle;
        cercle.setPosition(cercle.getPosition().x, tailleY - rayon -0.1f);
        vitesseBille *= 1.03f;
    }
    
    particles.setEmitter(cercle.getPosition());
    particles.update(deltaTime);
}


//-- Déplacement des Paddles --//
void GameState::paddlesInput(sf::Time deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        rectangle.move(0.f, -paddleSpeed * deltaTime.asSeconds());
    if (rectangle.getPosition().y < tailleRect.y/2.f)
        rectangle.setPosition(rectangle.getPosition().x, tailleRect.y/2.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        rectangle.move(0.f, paddleSpeed * deltaTime.asSeconds());
    if (rectangle.getPosition().y > tailleY - tailleRect.y/2.f)
        rectangle.setPosition(rectangle.getPosition().x, tailleY - tailleRect.y/2.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        rectangle2.move(0.f, -paddleSpeed * deltaTime.asSeconds());
    if (rectangle2.getPosition().y < tailleRect.y/2.f)
        rectangle2.setPosition(rectangle2.getPosition().x, tailleRect.y/2.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        rectangle2.move(0.f, paddleSpeed * deltaTime.asSeconds());
    if (rectangle2.getPosition().y > tailleY - tailleRect.y/2.f)
        rectangle2.setPosition(rectangle2.getPosition().x, tailleY - tailleRect.y/2.f);
}
