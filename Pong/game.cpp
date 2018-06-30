#include "game.hpp"

Game::Game(): tailleX(800), tailleY(600), tailleBordureRect(4), rayon(15), bordureBille(3), pi(3.141593)
{
	//-- Loading --//
	if (!font.loadFromFile(resourcePath() + "FiraSans-Light.otf")){
		std::cout << "Error loading font !" << std::endl;
	}
	if (!icon.loadFromFile(resourcePath() + "icon.jpeg")) {
		return EXIT_FAILURE;
	}
	//Chris_Zabriskie_-_01_-_The_Temperature_of_the_Air_on_the_Bow_of_the_Kaleetan -- Open Source !
	if (!music.openFromFile(resourcePath() + "kaleetan.ogg")) {
		return EXIT_FAILURE;
	}
	music.setLoop(true);
	if (!ballSoundBuffer.loadFromFile(resourcePath() + "ball.wav")){
		return EXIT_FAILURE;
	}
	ballSound.setBuffer(ballSoundBuffer);
	
	
	//-- Forging --//
	tailleRect.x = tailleX/25;
	tailleRect.y = tailleY/4;
	paddleSpeed = 550.f;
	vitesseBille = 350.f;
	angle = 3*pi/4;
	
	//Paddle Gauche
	rectangle.setSize(tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f);
	rectangle.setOrigin((tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f)/2.f);
	rectangle.setOutlineThickness(tailleBordureRect);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setPosition(tailleX/16, tailleY/2);
	rectangle.setFillColor(sf::Color::Transparent);
	
	//Paddle Droit
	rectangle2.setSize(tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f);
	rectangle2.setOrigin((tailleRect - sf::Vector2f(tailleBordureRect, tailleBordureRect)*2.f)/2.f);
	rectangle2.setOutlineThickness(tailleBordureRect);
	rectangle2.setOutlineColor(sf::Color::White);
	rectangle2.setPosition(tailleX-tailleX/16, tailleY/2);
	rectangle2.setFillColor(sf::Color::Transparent);
	
	//Balle
	cercle.setRadius(rayon - bordureBille);
	cercle.setOrigin(sf::Vector2f(rayon - bordureBille, rayon - bordureBille));
	cercle.setOutlineThickness(bordureBille);
	cercle.setOutlineColor(sf::Color::White);
	cercle.setPosition(tailleX/2, tailleY/2);
	cercle.setFillColor(sf::Color(170, 0, 170));
	
	
	//Message Pause
	messageBienvenue.setFont(font);
	messageBienvenue.setCharacterSize(40);
	messageBienvenue.setFillColor(sf::Color::White);
	messageBienvenue.setString("Bienvenue sur le Pong de Samuel !!!");
	
	message2.setFont(font);
	message2.setCharacterSize(30);
	message2.setFillColor(sf::Color::White);
	message2.setString("Espace pour commencer");
	
	
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
}

void Game::restart()
{
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
	
	
	
}

bool Game::update(float deltaTime)
{
	cercle.move(std::cos(angle) * vitesseBille * deltaTime, std::sin(angle) * vitesseBille * deltaTime);
	
	if(cercle.getPosition().x - rayon < 0.f){
		std::cout << "Red won !" << std::endl;
		messageBienvenue.setString("Rouge Gagne !!!");
		messageBienvenue.setCharacterSize(60);
		message2.setString("Echap pour quitter...");
		return false;
	}
	
	if(cercle.getPosition().x + rayon > tailleX){
		std::cout << "Blue won !" << std::endl;
		messageBienvenue.setString("Bleu Gagne !!!");
		messageBienvenue.setCharacterSize(60);
		message2.setString("Echap pour quitter...");
		return false;
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
	
	if (cercle.getPosition().x - rayon < rectangle.getPosition().x + tailleRect.x / 2 &&
		cercle.getPosition().x - rayon > rectangle.getPosition().x &&
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
		cercle.getPosition().x + rayon < rectangle2.getPosition().x &&
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
	
	return true;
}

void Game::run()
{
	music.play();
	sf::RenderWindow window(sf::VideoMode(tailleX, tailleY, 32), "Pong");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	sf::View vue = window.getDefaultView();
	vue.setCenter(400, 300);
	window.setView(vue);
	sf::Clock clock;
	
	float deltaTime = clock.restart().asSeconds();
	bool enJeu = false;
	 ParticleSystem particles(1000);
	particles.resize(window.getSize().x * 10);
	
	while (window.isOpen())
	{
		sf::Event event;
		
		if (enJeu)
		{
			sf::Time partiChron = clock.restart();
			deltaTime = partiChron.asSeconds();
			
			
			while (window.pollEvent(event))
			{
				if ( (event.type == sf::Event::Closed) || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) ) )
				{
					enJeu = false;
					std::cout << "Escape !!!" << std::endl;
				}
				if (event.type == sf::Event::Resized)
				{
					float zoom = 1.f;
					if(static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) > static_cast<float>(tailleX) / static_cast<float>(tailleY)) // x trop grands
					{
						zoom = static_cast<float>(window.getSize().y) / static_cast<float>(tailleY);
					}
					else // y trop grands
					{
						zoom = static_cast<float>(window.getSize().x) / static_cast<float>(tailleX);
					}
					vue.setViewport(sf::FloatRect((1-zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x))/2, (1-zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y))/2, zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x), zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y)));
					
					window.setView(vue);
					
					particles.resize(window.getSize().x * 10);
				}
			}
			
			//Déplacements des Paddles
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z))  && rectangle.getPosition().y > tailleRect.y/2.f)
			{rectangle.move(0.f, -paddleSpeed * deltaTime);}
			
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && rectangle.getPosition().y < tailleY - tailleRect.y/2.f)
			{rectangle.move(0.f, paddleSpeed * deltaTime);}
			
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && rectangle2.getPosition().y > tailleRect.y/2.f)
			{rectangle2.move(0.f, -paddleSpeed * deltaTime);}
			
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && rectangle2.getPosition().y < tailleY - tailleRect.y/2.f)
			{rectangle2.move(0.f, paddleSpeed * deltaTime);}
			
			
			if(!update(deltaTime))
				enJeu = false;
			
			particles.setEmitter(cercle.getPosition());
			particles.update(partiChron);
			
			window.clear(sf::Color::Black);
			
			window.draw(fond);
			window.draw(rectangle);
			window.draw(rectangle2);
			window.draw(particles);
			window.draw(cercle);
			
			
			window.display();
		}
		
		
		else //enJeu == false
		{
			while (window.pollEvent(event))
			{
				if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				{window.close();}
				
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
				{
					restart();
					particles.reset();
					enJeu = true;
					clock.restart();
				}
				if (event.type == sf::Event::Resized)
				{
					// on met à jour la vue, avec la nouvelle taille de la fenêtre
					float zoom = 1.f;
					if(static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) > static_cast<float>(tailleX) / static_cast<float>(tailleY)) // x trop grands
					{
						zoom = static_cast<float>(window.getSize().y) / static_cast<float>(tailleY);
					}
					else // y trop grands
					{
						zoom = static_cast<float>(window.getSize().x) / static_cast<float>(tailleX);
					}
					vue.setViewport(sf::FloatRect((1-zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x))/2, (1-zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y))/2, zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x), zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y)));
					
					window.setView(vue);
					
					particles.resize(window.getSize().x * 10);
				}
			}
			
			
			
			window.clear(sf::Color::Black);
			window.draw(fond);
			window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
			messageBienvenue.setPosition((window.getSize().x-messageBienvenue.getGlobalBounds().width)/2, window.getSize().y/3);
			message2.setPosition((window.getSize().x-message2.getGlobalBounds().width)/2, window.getSize().y*3/4);
			window.draw(messageBienvenue);
			window.draw(message2);
			window.setView(vue);
			window.display();
		}
		
		
	}//window.isOpen()
}//main()
