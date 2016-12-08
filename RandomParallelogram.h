#pragma once
#include "AbstractParallelogramState.h"

class Parallelogram;

class RandomParalellogram : public AbstractParallelogramState
{
public:
	void getMonochrome(Parallelogram& _object)const;
	bool isMonochrome()const;
};


