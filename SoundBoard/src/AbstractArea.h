#pragma once

#include <SFML/Graphics.hpp>
#include "SoundMaker.h"
#include <functional>

class AbstractArea
{
private:
	bool isWithinArea(unsigned x, unsigned y);

protected:
	sf::Shape* shape_;
	float x_, y_;
	float width_, height_;
	sf::Color color_;
	bool removable_;
	bool ready_;

public:
	AbstractArea() : removable_(false) { shape_ = NULL; }
	AbstractArea(float x, float y, float width, float height) 
		: x_(x), y_(y), width_(width), height_(height), removable_(false) {}
	AbstractArea(float x, float y, float width, float height, sf::Color color) 
		: x_(x), y_(y), width_(width), height_(height), color_(color), removable_(false) {}	
	AbstractArea(sf::Shape* shape) : shape_(shape), removable_(false), ready_(true) {}
	virtual ~AbstractArea();

	float x() { return shape_->getPosition().x; }
	float y() { return shape_->getPosition().y; }
	float width() { return width_; }
	float height() { return height_; }
	void setX(float x) { shape_->setPosition(x, y()); }
	void setY(float y) { shape_->setPosition(x(), y); }
	void setW(float w) { width_ = w; }
	void setH(float h) { height_ = h; }
	bool removable() { return removable_; }
	bool ready() { return ready_; }
	void setColor(sf::Color color) { color_ = color; }
	virtual void update(unsigned int x, unsigned int y, sf::Clock);
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
	SoundArea(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq);
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
	sf::RectangleShape* progress_shape_;
	std::function<void()> action_;
	sf::Sprite btn_sprite_;	
	sf::Text btn_text_;

	void setProgress(float percentage);
public:
	// change to texture
	Button(sf::Shape* shape);
	Button(sf::Vector2f position, sf::Vector2f size, std::string text);
	Button(float x, float y, float width, float height, sf::Color color)
		: AbstractArea(x, y, width, height, color), inside_(false), enabled_(true), enterTime_(0L), progress_(0.0f), MAX_TIME(1.0f) {}
	~Button() { delete progress_shape_; }
	void setAction(std::function<void()> action) { action_ = action; }
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
	virtual void draw(sf::RenderWindow* render_window);
};

///////////////////////////
//(ABSTRACT) MOVING AREA //
///////////////////////////
class MovingArea : public AbstractArea
{
private:
	float time_target_;
	float position_delay_;
	int position_delta_;
	bool action_performed;
	sf::Clock *clock_;
protected:
	float speed_, time_correction_;
public:
	MovingArea(sf::Rect<float> rect, float current_time, float time_delay, int position_delta);
	MovingArea::MovingArea(sf::Rect<float> rect);
	virtual ~MovingArea() {}
	void setClock(sf::Clock *clock) { clock_ = clock; }
	void setSpeed(float speed) { speed_ = speed; }
	void setPostionTarget(float target) { position_delta_ = target; }
	
	virtual void draw(sf::RenderWindow* render_window);	
};

///////////////////////
// SOUND MOVING AREA //
///////////////////////
class SoundMovingArea : public MovingArea
{
private:	
	StkFloat baseFreq_;
	SoundMaker soundMaker_;
	sf::Color hover_color_;
	sf::Color idle_color_;

public:
	SoundMovingArea(sf::Rect<float> rect, float current_time, float time_delay, int position_delta);
	SoundMovingArea(sf::Rect<float> rect) : MovingArea(rect) {}
	~SoundMovingArea();
	void setInsrument(Instrmnt *instrument) { soundMaker_.setInstrument(instrument);}
	void setFrequency(StkFloat freq) { baseFreq_ = freq; }
	void openStream();
		
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);

};

class SoundMovingAreav2 : public SoundArea
{
public:
	SoundMovingAreav2(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq, sf::Vector2f final_position, float strat_t, float duration, sf::Vector2f velocity);
	~SoundMovingAreav2();

	sf::Vector2f initialPosition() { return initial_pos_; }
	sf::Vector2f finalPosition() { return final_position_; }
	float startTime() { return start_t_; }
	float endTime() { return end_t_; }
	sf::Shape* shape() { return shape_; }

	virtual void update(unsigned int x, unsigned int y, sf::Clock);
	virtual void draw(sf::RenderWindow* render_window);
private:
	sf::Vector2f initial_pos_, final_position_;
	sf::Vector2f velocity_;
	sf::RectangleShape *track_shape_;
	sf::RectangleShape *outline_shape_;
	float start_t_, end_t_;
	static const float PREPARE_TIME;
	static const float INITIAL_SCALE;

	void updateBlock(sf::Clock clock);
	void updateOutline(sf::Clock clock);
};