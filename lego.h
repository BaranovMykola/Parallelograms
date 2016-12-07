#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>

using std::ostream;
using std::istream;

enum COLOR{RED, GREEN, BLUE};
const int colors = 3;
const std::vector<char*> colors_text = { "Red", "Green", "Blue" };
const unsigned int max_lenght = 20;

struct Lego
{
	unsigned short type;
	unsigned short lenght;
	Lego();
	Lego(unsigned short, unsigned short);
	~Lego();
	friend ostream& operator<<(ostream&, const Lego&);
	friend istream& operator>>(istream&, Lego&);
};
