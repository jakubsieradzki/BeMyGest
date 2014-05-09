#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <SFML/Graphics.hpp>

namespace Utils 
{
	enum LogType
	{
		MONITOR = 1,
		FILE = 2,
		MONITOR_AND_FILE = 3,
		OTHER = 4
	};
}

enum EnemyType
{
	PIRANIA = 1,
	BECZKA = 2,
	ZDECHLA = 3
};

enum InputType
{
	MOUSE = 1,
	KEYBOARD = 2
};

const char DEFAULT_EMPTY_TILE = '*';
const char DEFAULT_EMPTY_TILE2 = 'O';
const int MAX_ASSETS_NUMBER = 10000;
const float MAX_SCORE = 100.0f;
const int MAX_RATIO_SCORE = 3;
const InputType DEFAULT_INPUT_TYPE = MOUSE;
const float MOVE_SPEED = 5.0f;
const float MOVE_X_SPEED = 8.0f;
const float MOVE_Y_SPEED = 6.0f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float RADIUS = 50.0f;
const float MAX_MOUSE_ACCELERATION_RADIUS = 300.0f;
const float MIN_MOUSE_ACCELERATION_RADIUS = 10.0f;
const float MAX_SPEED = 3.0f;
const float MAX_PLAYER_RADIUS = 100.0f;
const float STANDARD_WAVES_SPEED = 2.0f;
const float PIRANIA_SPEED = 3.0f;
const float ZDECHLA_SPEED = 3.0f;

const float MOVE_SPACE_WIDTH = 200.0f;
const float MOVE_SPACE_TOP_OFFSET = 80.0f;
const float MOVE_SPACE_BOTTOM_OFFSET = 50.0f;

const int MAX_SECONDS_FOR_LEVEL = 250;

// graphics
const sf::Color DEFAULT_TRANSPARENCY_MASK = sf::Color(255, 0, 255);
const std::string TEXTURE_NOT_FOUND = "resource/gfx/not_found.bmp";
// log
const std::string LOG_DEFAULT_PATH = "log.txt";

// tile 
struct Tile
{
	Tile() : sign(DEFAULT_EMPTY_TILE), row(1), col(1) {};

	char sign;
	int row, col;
};

#endif