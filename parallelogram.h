#pragma once
#include <exception>
#include <fstream>
#include <algorithm>
#include "Lego.h"
#include <memory>
#include "AbstractParallelogramState.h"

enum PICE{LEFT, TOP, RIGHT, BOTTOM};
const int sides = 4;

using namespace std;

class Parallelogram
{
public:
	Parallelogram();
	Parallelogram(Lego, Lego, Lego, Lego);
	Parallelogram(const Parallelogram&);
	explicit Parallelogram(bool);
	~Parallelogram()=default;
	unsigned short getPredominantColor()const;
	void getState()const;
	void tryMonohrome();
	friend ostream& operator<<(ostream&, const Parallelogram&);
	friend istream& operator>>(istream&, Parallelogram&);
	Parallelogram& operator=(const Parallelogram&);
	bool getType()const;
	Lego getPiece(unsigned short)const;
	unsigned int getResistibility()const;

private:
	Lego piece[4];
	unsigned int resistibility;
	friend class AbstractParallelogramState;
	friend class RandomParalellogram;

	unique_ptr<AbstractParallelogramState> current;

	bool isMonochrome()const;
	void trySides()const;
};

