#include "AbstractArea.h"

AbstractArea::~AbstractArea()
{

}

void AbstractArea::update(unsigned int x, unsigned int y)
{
	if (isWithinArea(x, y))
	{
		onHover(x, y);
	}
	else
	{
		onLeave(x, y);
	}
}

void AbstractArea::draw(bmg::GlueGL *glue)
{
	glue->DrawRectangleWithColor(x_, y_, width_, height_, color_.r, color_.g, color_.b);
}

bool AbstractArea::isWithinArea(unsigned x, unsigned y)
{
	return 
		x > x_ && x < x_ + width_
		&&
		y > y_ && y < y_ + height_;
}