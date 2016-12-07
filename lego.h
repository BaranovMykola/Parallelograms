#pragma once
#include <fstream>
#include <algorithm>
#include <vector>

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
	Lego() = default;
	Lego(unsigned short, unsigned short);
	~Lego() = default;
	friend ostream& operator<<(ostream&, const Lego&);
	friend istream& operator>>(istream&, Lego&);
};