#pragma once

class Parallelogram;

class AbstractParallelogramState
{
public:
	virtual ~AbstractParallelogramState() = default;
	virtual void getMonochrome(Parallelogram&)const = 0;
	virtual bool isMonochrome()const = 0;
};
