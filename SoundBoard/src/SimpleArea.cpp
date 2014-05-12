#include "AbstractArea.h"

void SimpleArea::onHover(unsigned int x, unsigned y)
{
	color_ = changeColor_;
}

void SimpleArea::onLeave(unsigned int x, unsigned y)
{
	color_ = initializeColor_;
}