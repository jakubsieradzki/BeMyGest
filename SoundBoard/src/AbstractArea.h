#pragma once

#include <SFML/Graphics.hpp>
#include "SoundMaker.h"
#include <functional>

class AbstractArea
{
private:
	bool isWithinArea(unsigned x, unsigned y);

protected:
	float x_, y_;
	float width_, height_;
	sf::Color color_;

public:
	AbstractArea(float x, float y, float width, float height) 
		: x_(x), y_(y), width_(width), height_(height) {}
	AbstractArea(float x, float y, float width, float height, sf::Color color) 
		: x_(x), y_(y), width_(width), height_(height), color_(color) {}
	virtual ~AbstractArea();

	float x() { return x_; }
	float y() { return y_; }
	float width() { return width_; }
	float height() { return height_; }
	void setColor(sf::Color color) { color_ = color; }
	void update(unsigned int x, unsigned int y);
	virtual void draw(sf::RenderWindow* render_window);
	// events
	virtual void onHover(unsigned int x, unsigned int y) = 0;
	virtual void onLeave(unsigned int x, unsigned int y) = 0;
};

/////////////////
// SIMPLE AREA //
/////////////////
class SimpleArea : public AbstractArea
{
private:
	sf::Color initializeColor_;
	sf::Color changeColor_;

public:
	SimpleArea(float x, float y, float width, float height, sf::Color color, sf::Color changeColor) 
		: AbstractArea(x, y, width, height, color), initializeColor_(color), changeColor_(changeColor) {}
	
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
};

////////////////
// SOUND AREA //
////////////////
class SoundArea : public AbstractArea
{
private:
	SoundMaker soundMaker_;
	StkFloat baseFreq_;

public:
	SoundArea(
		float x, 
		float y,
		float width,
		float height,
		sf::Color color,
		Instrmnt *instrument,
		StkFloat baseFreq);
	~SoundArea() { soundMaker_.closeStream(); }
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
};

////////////
// BUTTON //
////////////
class Button : public AbstractArea
{
private:
	bool inside_, enabled_;
	clock_t enterTime_;	
	float progress_, MAX_TIME;
	std::function<void()> action_;
public:
	// change to texture
	Button(float x, float y, float width, float height, sf::Color color)
		: AbstractArea(x, y, width, height, color), inside_(false), enabled_(true), enterTime_(0L), progress_(0.0f), MAX_TIME(1.0f) {}
	~Button() {}
	void setAction(std::function<void()> action) { action_ = action; }
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
	virtual void draw(sf::RenderWindow* render_window);
};

/////////////////
// MOVING AREA //
/////////////////
class MovingArea : public AbstractArea
{
private:
	float time_delay_, update_time_, speed_;
	int position_delta_;
	bool action_performed;
	sf::Clock clock_;
public:
	MovingArea(sf::Rect<float> rect, float time_delay, int position_delta);
	void setClock(sf::Clock clock) { clock_ = clock; }

	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
	virtual void draw(sf::RenderWindow* render_window);
};