#pragma once
#include "AbstractParallelogramState.h"

class Parallelogram;

class MonochromeParallelogram : public AbstractParallelogramState
{
public:
	void getMonochrome(Parallelogram&)const;
	bool isMonochrome()const;
};