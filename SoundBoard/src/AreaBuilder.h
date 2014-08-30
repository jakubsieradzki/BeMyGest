#pragma once

template<class T>
class AreaBuilder
{
public:
	virtual T* build() = 0;
};