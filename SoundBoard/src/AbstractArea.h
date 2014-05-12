#ifndef ABSTRACT_AREA_
#define ABSTRACT_AREA_

#include "../dep/GlueGL.h"
#include "SoundMaker.h"

struct AreaColor
{
	float r,g,b,alpha;

	AreaColor() : r(1.0), g(1.0), b(1.0), alpha(1.0) {}
	AreaColor(float _r, float _g, float _b, float _alpha)
		: r(_r), g(_g), b(_b), alpha(_alpha) {}
};

class AbstractArea
{
private:
	bool isWithinArea(unsigned x, unsigned y);

protected:
	unsigned x_, y_, width_, height_;
	AreaColor color_;

public:
	AbstractArea(unsigned x, unsigned y, unsigned width, unsigned height) 
		: x_(x), y_(y), width_(width), height_(height) {}
	AbstractArea(unsigned x, unsigned y, unsigned width, unsigned height, AreaColor color) 
		: x_(x), y_(y), width_(width), height_(height), color_(color) {}
	virtual ~AbstractArea();

	unsigned x() { return x_; }
	unsigned y() { return y_; }
	unsigned width() { return width_; }
	unsigned height() { return height_; }
	void setColor(AreaColor color) { color_ = color; }
	void update(unsigned int x, unsigned int y);
	virtual void draw(bmg::GlueGL *glue);
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
	AreaColor initializeColor_;
	AreaColor changeColor_;

public:
	SimpleArea(unsigned x, unsigned y, unsigned width, unsigned height, AreaColor color, AreaColor changeColor) 
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
		AreaColor color,
		Instrmnt *instrument,
		StkFloat baseFreq);
	~SoundArea() { soundMaker_.closeStream(); }
	virtual void onHover(unsigned int x, unsigned int y);
	virtual void onLeave(unsigned int x, unsigned int y);
};

#endif