#ifndef AREA_MANAGER_
#define AREA_MANAGER

#include "../dep/GlueGL.h"
#include "AbstractArea.h"
#include <vector>

class AreaManager
{
private:
	bmg::GlueGL *glue_;
	std::vector<AbstractArea*> areas_;

	bool isWithinArea(AbstractArea *area, unsigned x, unsigned y); 
public:
	AreaManager(bmg::GlueGL *glue) : glue_(glue) {}
	~AreaManager();
	void addArea(AbstractArea * area) { areas_.push_back(area); }
	void draw();
	void update(unsigned int x, unsigned int y);
};

#endif 