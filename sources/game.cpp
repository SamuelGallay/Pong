#include "game.hpp"

#if SAM_XCODE
#else
std::string resourcePath()
{
	return "media/";
}
#endif

Game::Game(): window(sf::VideoMode(tailleX, tailleY, 32), "Pong"), particles(1000), tailleX(800), tailleY(600), tailleBordureRect(4), rayon(15), bordureBille(3), pi(3.141593)
{
	//-- Loading --//
	font.loadFromFile(resourcePath() + "FiraSans-Light.otf");
	icon.loadFromFile(resourcePath() + "icon.jpeg");
	music.openFromFile(resourcePath() + "kaleetan.ogg");
	ballSoundBuffer.loadFromFile(resourcePath() + "ball.wav");
	
	//Chris_Zabriskie_-_01_-_The_Temperature_of_the_Air_on_the_Bow_of_the_Kaleetan -- Open Source !
	music.setLoop(true);
	ballSound.setBuffer(ballSoundBuffer);
	
	//-- Window --//
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
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
	
	//-- Messages...--//
	
	//Bienvenue
	messageBienvenue.setFont(font);
	messageBienvenue.setCharacterSize(40);
	messageBienvenue.setFillColor(sf::Color::White);
	messageBienvenue.setString("Bienvenue sur le Pong de Samuel !!!");
	
	//Message 2
	message2.setFont(font);
	message2.setCharacterSize(30);
	message2.setFillColor(sf::Color::White);
	message2.setString("Espace pour commencer");
	
	//Message 3
	message3.setFont(font);
	message3.setCharacterSize(50);
	message3.setFillColor(sf::Color::White);
	message3.setString("Vitesse");
	
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
}

//-- Fonction Principale --//
void Game::run()
{
	music.play();
	float deltaTime = clock.restart().asSeconds();
	enJeu = false;
	
	while (window.isOpen())
	{
		processEvents();
		if (enJeu) {
			sf::Time deltaTime = clock.restart();
			paddlesInput(deltaTime);
			update(deltaTime);
		}
		updateMessages();
		render();
	}
}

//-- Dessine à l'écran --//
void Game::render()
{
	window.clear(sf::Color::Black);
	window.draw(fond);
	
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
	if(enJeu){
		window.draw(blue);
		window.draw(red);
		window.draw(message3);
	}
	else{
		window.draw(message3);
		window.draw(messageBienvenue);
		window.draw(message2);
	}
	
	window.setView(vue);
	if(enJeu){
		window.draw(rectangle);
		window.draw(rectangle2);
		window.draw(particles);
		window.draw(cercle);
	}
	window.display();
}

//-- Recommence une Partie --//
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

//Actualise le jeu dans une partie --//
void Game::update(sf::Time deltaTime)
{
	cercle.move(std::cos(angle) * vitesseBille * deltaTime.asSeconds(), std::sin(angle) * vitesseBille * deltaTime.asSeconds());
	
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
	
	enJeu = true;
	if(cercle.getPosition().x - rayon < 0.f){
		messageBienvenue.setString("Rouge Gagne !!!");
		messageBienvenue.setCharacterSize(60);
		message2.setString("Echap pour quitter...");
		score.y++;
		red.setString(std::to_string(score.y));
		enJeu = false;
	}
	if(cercle.getPosition().x + rayon > tailleX){
		messageBienvenue.setString("Bleu Gagne !!!");
		messageBienvenue.setCharacterSize(60);
		message2.setString("Echap pour quitter...");
		score.x++;
		blue.setString(std::to_string(score.x));
		enJeu = false;
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

//-- S'occupe des événements --//
void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if ( (event.type == sf::Event::Closed) || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape) ) )
		{
			if (enJeu) {
				enJeu = false;
				messageBienvenue.setCharacterSize(40);
				messageBienvenue.setString("Bienvenue sur le Pong de Samuel !!!");
				message2.setString("Echap pour quitter...");
			}
			else
				window.close();
			
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
		{
			if(!enJeu){
				restart();
				clock.restart();
				particles.setEmitter(cercle.getPosition());
				particles.reset();
				enJeu = true;
				
			}
			else{
				enJeu = false;
				messageBienvenue.setString("Pause");
				messageBienvenue.setCharacterSize(60);
				message2.setString("Espace pour (re)commencer");
			}
		}
		
		if (event.type == sf::Event::Resized)
		{
			float zoom = 1.f;
			if(static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y) > static_cast<float>(tailleX) / static_cast<float>(tailleY)){
				zoom = static_cast<float>(window.getSize().y) / static_cast<float>(tailleY);
			}
			else{
				zoom = static_cast<float>(window.getSize().x) / static_cast<float>(tailleX);
			}
			
			vue.setViewport(sf::FloatRect((1-zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x))/2, (1-zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y))/2, zoom*static_cast<float>(tailleX)/static_cast<float>(window.getSize().x), zoom*static_cast<float>(tailleY)/static_cast<float>(window.getSize().y)));
			window.setView(vue);
			particles.resize(window.getSize().x * 5);
		}
	}
}

//-- Déplacement des Paddles --//
void Game::paddlesInput(sf::Time deltaTime)
{
	//Déplacements des Paddles
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z))  && rectangle.getPosition().y > tailleRect.y/2.f)
	{rectangle.move(0.f, -paddleSpeed * deltaTime.asSeconds());}
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && rectangle.getPosition().y < tailleY - tailleRect.y/2.f)
	{rectangle.move(0.f, paddleSpeed * deltaTime.asSeconds());}
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && rectangle2.getPosition().y > tailleRect.y/2.f)
	{rectangle2.move(0.f, -paddleSpeed * deltaTime.asSeconds());}
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && rectangle2.getPosition().y < tailleY - tailleRect.y/2.f)
	{rectangle2.move(0.f, paddleSpeed * deltaTime.asSeconds());}
}

//-- Positionne et écrit les messages (sans les afficher) --//
void Game::updateMessages()
{
	if (enJeu) {
		message3.setString(std::to_string(static_cast<int>(vitesseBille)));
		message3.setPosition((window.getSize().x-message3.getGlobalBounds().width)/2, window.getSize().y*0/8);
		blue.setPosition(window.getSize().x/4 - blue.getGlobalBounds().width/2, window.getSize().y/2 - blue.getGlobalBounds().height/2);
		red.setPosition(window.getSize().x*3/4 - red.getGlobalBounds().width/2, window.getSize().y/2 - red.getGlobalBounds().height/2);
	}
	else{
		messageBienvenue.setPosition((window.getSize().x-messageBienvenue.getGlobalBounds().width)/2, window.getSize().y/3);
		message2.setPosition((window.getSize().x-message2.getGlobalBounds().width)/2, window.getSize().y*3/4);
		message3.setPosition((window.getSize().x-message3.getGlobalBounds().width)/2, window.getSize().y*0/8);
	}
}

