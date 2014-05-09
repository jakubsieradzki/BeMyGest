#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include "global.h"
#include "GameMgr.h"
#include "Entity.h"
#include "Seashell.h"
#include "Enemy.h"
#include "Starfish.h"
#include "GfxLoader.h"
#include "Map.h"
#include "MapFile.h"
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Electricus", sf::Style::Default);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(50);
	sf::Font font;// = sf::Font();
	bool stop = false;

	Map map(10, 15, 50);
	map.setGrid(true);
	MapFile mapFile1("resource/map/1.txt");

	GameMgr::getInstance().loadSounds();
	GameMgr::getInstance().setCellSize(map.rowSize, map.colSize);
	sf::Music* bg_music = new sf::Music();
	bg_music -> openFromFile("resource/sfx/background.ogg");
	bg_music -> setVolume(70.0f);
	sf::Clock level_clock;

	sf::Texture* beczka = Data::GfxLoader::getInstance().loadTexture("resource/beczka.png");
	sf::Texture* ryba = Data::GfxLoader::getInstance().loadTexture("resource/ryba.png");
	sf::Texture* starfish = Data::GfxLoader::getInstance().loadTexture("resource/starfish.png");
	sf::Texture* zdechla_ryba = Data::GfxLoader::getInstance().loadTexture("resource/zdechla_ryba.png");
	sf::Texture* muszla1 = Data::GfxLoader::getInstance().loadTexture("resource/muszla.png");
	sf::Texture* muszla2 = Data::GfxLoader::getInstance().loadTexture("resource/muszla2.png");

	// umieszcamy assety na mapie nr 1
	for(int i = 0; i < (mapFile1.size); ++i)
	{
		Tile* temp = mapFile1.tiles[i];
		Entity* entity;

		switch(temp -> sign)
		{
			case 'M': // muszla1
				entity = new Seashell(muszla1);
				((Seashell*)entity) -> setScore(5);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.2f, 0.2f);
				map.setEntity(entity, temp -> row, temp -> col);
				break;
			case 'N': // muszla2
				entity = new Seashell(muszla2);
				((Seashell*)entity) -> setScore(5);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.3f, 0.3f);
				map.setEntity(entity, temp -> row, temp -> col);
				break;
			case 'B': // beczka
				entity = new Enemy(beczka);
				((Enemy*)entity) -> setScore(7);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.4f, 0.4f);
				map.setEntity(entity, temp -> row, temp -> col);
				((Enemy*)entity) -> setType(BECZKA);
				break;
			case 'R': // ryba
				entity = new Enemy(ryba);
				((Enemy*)entity) -> setScore(15);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.2f, 0.2f);
				map.setEntity(entity, temp -> row, temp -> col);
				((Enemy*)entity) -> setType(PIRANIA);
				break;
			case 'S': // starfish
				entity = new Starfish(starfish);
				//((Starfish*)entity) -> setScoreRatio(2);
				((Starfish*)entity) -> setScore(20);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.15f, 0.15f);
				map.setEntity(entity, temp -> row, temp -> col);
				break;
			case 'Z': // zdechla ryba
				entity = new Enemy(zdechla_ryba);
				((Enemy*)entity) -> setScore(5);
				entity -> setX((temp -> col) * (map.colSize));
				entity -> setScale(0.2f, 0.2f);
				map.setEntity(entity, temp -> row, temp -> col);
				((Enemy*)entity) -> setType(ZDECHLA);
				break;
			default:
				break;
		}
	}

	sf::Texture* fish1 = Data::GfxLoader::getInstance().loadTexture("resource/wegorz1.png");
	sf::Texture* fish2 = Data::GfxLoader::getInstance().loadTexture("resource/wegorz2.png");
	sf::Texture* fish3 = Data::GfxLoader::getInstance().loadTexture("resource/wegorz3.png");
	Player* fish = new Player(fish1);
	fish -> setScale(0.8f, 0.8f);
	fish -> sprite -> setPosition(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
	fish -> setOrigin(135.0f, 24.5f);
	fish -> setSmallerCollisionAura();
	fish -> refresh();
	
	sf::Texture* waves = Data::GfxLoader::getInstance().loadTexture("resource/fale.png");
	sf::Sprite* waves1 = new sf::Sprite(*waves);
	sf::Sprite* waves2 = new sf::Sprite(*waves);

	sf::Texture* line = Data::GfxLoader::getInstance().loadTexture("resource/linia.png");
	sf::Sprite* line1 = new sf::Sprite(*line);
	sf::Sprite* line2 = new sf::Sprite(*line);

	float left_boundry = (SCREEN_WIDTH-MOVE_SPACE_WIDTH)/2.0f;
	float right_boundry = SCREEN_WIDTH-(SCREEN_WIDTH-MOVE_SPACE_WIDTH)/2.0f;

	line1 -> setPosition(left_boundry, 0.0f);
	line2 -> setPosition(right_boundry, 0.0f);

	waves1 -> setPosition(-SCREEN_WIDTH/2.0f, 0.0f);
	waves2 -> setPosition(SCREEN_WIDTH/2.0f, 0.0f);

	float xLeftSide = 0.0f;
	// music
	bg_music -> setLoop(true);
	bg_music -> play();
	level_clock.restart();
	int currentSecond = MAX_SECONDS_FOR_LEVEL;
	sf::Text* textScore, *textClock, *textScored;

	while(window.isOpen())
	{
		window.clear();
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				bg_music ->stop();
				window.close();
			}
		}

		int xMousePosition = sf::Mouse::getPosition(window).x;
		int yMousePosition = sf::Mouse::getPosition(window).y;		
		float vectorX = xMousePosition - SCREEN_WIDTH/2.0f;
		float vectorY = yMousePosition - SCREEN_HEIGHT/2.0f;

		float magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);

		if(magnitude == 0.0f)
			magnitude = 0.01f;

		vectorX /= magnitude;
		vectorY /= magnitude;

		magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);

		// wektor osi OX
		float axisX = 1.0f;
		float axisY = 0.0f;
		float magnituedAxis = sqrt(axisX*axisX+axisY*axisY);
		vectorY = -vectorY;
		magnitude = sqrt(vectorX*vectorX + vectorY*vectorY);
		// k�t mi�dzy osi� OX a wektorem kierunku w�gorza
		float angle = acos((axisX*vectorX+axisY*vectorY)/(magnituedAxis*magnitude));
		angle = angle * 180.0f/boost::math::constants::pi<float>();
		
		float xMouseOffset = SCREEN_WIDTH/2.0f - xMousePosition;
		float yMouseOffset = SCREEN_HEIGHT/2.0f - yMousePosition;
		
		xMouseOffset = (xMouseOffset/(SCREEN_WIDTH/2.0f))*MOVE_X_SPEED;
		yMouseOffset = (yMouseOffset/(SCREEN_HEIGHT/2.0f))*MOVE_Y_SPEED;

		if(!stop)
		{
			textScore = new sf::Text("Punkty: " + boost::lexical_cast<std::string>(GameMgr::getInstance().getScore()), font, 25);
			textScore -> setPosition(10.0f, 0.0f);
			textScore -> setColor(sf::Color::Blue);
			textClock = new sf::Text("Czas: " + boost::lexical_cast<std::string>(currentSecond), font, 25);
			textClock -> setPosition(680.0f, 0.0f);
			textClock -> setColor(sf::Color::Blue);
		}
		else
		{
			textScored = new sf::Text("Zdobyte: " + boost::lexical_cast<std::string>(GameMgr::getInstance().getScore()) + " pkt.", font, 40);
			textScored -> setColor(sf::Color::Blue);
			textScored -> setPosition(280.0f, 280.0f);
		}

		if(vectorY > 0.0f)
		{
			fish -> sprite -> setRotation(-angle);
			fish -> collisionAura -> setRotation(-angle);
		}
		else
		{
			fish -> sprite -> setRotation(angle);
			fish -> collisionAura -> setRotation(angle);
		}

		static int fishNumber = 1;
		static int frameNumber = 1;

		switch(fishNumber) {
		case 1:
			fish -> sprite -> setTexture(*fish1);
			break;
		case 2:
			fish -> sprite -> setTexture(*fish2);
			break;
		case 3:
			fish -> sprite -> setTexture(*fish3);
			break;
		}
		
		if(++frameNumber > 6){
			if(++fishNumber>3)
				fishNumber = 1;
			frameNumber = 1;
		}
		if(!stop)
		{
			fish -> move(-xMouseOffset, -yMouseOffset);	

			if(fish -> sprite -> getPosition().x < left_boundry)
				fish -> setPosition(left_boundry, fish -> sprite -> getPosition().y);
			if(fish -> sprite -> getPosition().x > right_boundry)
				fish -> setPosition(right_boundry, fish -> sprite -> getPosition().y);
			if(fish -> sprite -> getPosition().y < MOVE_SPACE_TOP_OFFSET)
				fish -> setPosition(fish -> sprite -> getPosition().x, MOVE_SPACE_TOP_OFFSET);
			if(fish -> sprite -> getPosition().y > (SCREEN_HEIGHT - MOVE_SPACE_BOTTOM_OFFSET))
				fish -> setPosition(fish -> sprite -> getPosition().x, SCREEN_HEIGHT - MOVE_SPACE_BOTTOM_OFFSET);

			xLeftSide -= xMouseOffset;
			// animacja fali
			waves1 -> move(xMouseOffset, 0.0f);
			waves2 -> move(xMouseOffset, 0.0f);
		
			if(waves1 -> getPosition().x <= -(float)SCREEN_WIDTH)
			{
				waves1 -> setPosition((float)SCREEN_WIDTH, 0.0f);
				waves2 -> setPosition(0.0f, 0.0f);
			}
			else if (waves1 -> getPosition().x >= (float)SCREEN_WIDTH)
			{
				waves1 -> setPosition(-(float)SCREEN_WIDTH, 0.0f);
				waves2 -> setPosition(0.0f, 0.0f);
			}
			if(waves2 -> getPosition().x <= -(float)SCREEN_WIDTH)
			{
				waves2 -> setPosition((float)SCREEN_WIDTH, 0.0f);
				waves1 -> setPosition(0.0f, 0.0f);
			}
			else if(waves2 -> getPosition().x >= (float)SCREEN_WIDTH)
			{
				waves2 -> setPosition(-(float)SCREEN_WIDTH, 0.0f);
				waves1 -> setPosition(0.0f, 0.0f);
			}
		}
		// t�o
		window.draw(*waves1);
		window.draw(*waves2);

		// linie ograniczaj�ce ruch rybki
		window.draw(*line1);
		window.draw(*line2);

		// siatka mapy
		if(map.gridOn)
		{
			for(int i = 0; i < (map.rows); ++i)
			{
				window.draw(*(map.rowSprites[i]));
			}
			for(int j = 0; j < (map.cols); ++j)
			{
				window.draw(*(map.colSprites[j]));
			}
		}
		
		for(int i = 0; i < (map.counter); ++i)
		{
			// just for sure
			if((map.assets[i]) != NULL)
			{
				if(!stop)
					map.assets[i] -> animate(xMouseOffset);
 				if((!map.assets[i] -> remove) && (map.assets[i] -> x >= xLeftSide-300.0f))
				{
					if(map.assets[i] -> x < xLeftSide+SCREEN_WIDTH+300.0f)
					{
						// kolizje
						fish -> isCollides(map.assets[i]);
						// rysujemy
						window.draw(map.assets[i] -> getSprite());
						window.draw(map.assets[i] -> getCollisionAura());
					}
				}
			}
		}
	
		// PLAYAER
		window.draw(fish->getSprite());
		window.draw(fish->getCollisionAura());

		// GUI
		if(!stop)
		{
			window.draw(*textScore);
			window.draw(*textClock);
		}
		else
			window.draw(*textScored);

		window.display();
		if(level_clock.getElapsedTime().asSeconds() > 1.0f)
		{
			--currentSecond;
			level_clock.restart();
			if(currentSecond == 0)
				stop = true;
		}
	}
}