#ifndef ABSTRACT_AREA_
#define ABSTRACT_AREA_

#include <SFML/Graphics.hpp>
#include "SoundMaker.h"
#include <functional>

class AbstractArea
{
private:
	bool isWithinArea(unsigned x, unsigned y);

protected:
	unsigned x_, y_, width_, height_;
	sf::Color color_;

public:
	AbstractArea(unsigned x, unsigned y, unsigned width, unsigned height) 
		: x_(x), y_(y), width_(width), height_(height) {}
	AbstractArea(unsigned x, unsigned y, unsigned width, unsigned height, sf::Color color) 
		: x_(x), y_(y), width_(width), height_(height), color_(color) {}
	virtual ~AbstractArea();

	unsigned x() { return x_; }
	unsigned y() { return y_; }
	unsigned width() { return width_; }
	unsigned height() { return height_; }
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
	SimpleArea(unsigned x, unsigned y, unsigned width, unsigned height, sf::Color color, sf::Color changeColor) 
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
		unsigned x, 
		unsigned y,
		unsigned width,
		unsigned height,
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
	Button(unsigned x, unsigned y, unsigned width, unsigned height, sf::Color color)
		: AbstractArea(x, y, width, height, color), inside_(false), enabled_(true), enterTime_(0L), progress_(0.0f), MAX_TIME(1.0f) {}
	~Button() {}
	void setAction(std::function<void()> action) { action_ = action; }
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
	virtual void draw(sf::RenderWindow* render_window);
};

#endif