#include "Parallelogram.h"
#include "MonochromeParallelogram.h"
#include "RandomParallelogram.h"


Parallelogram::Parallelogram():
	current(new RandomParalellogram),
	resistibility(0)
{
}

Parallelogram::Parallelogram(Lego _left, Lego _top, Lego _right, Lego _bottom):
	resistibility(0)
{
	piece[LEFT] = _left;
	piece[TOP] = _top;
	piece[RIGHT] = _right;
	piece[BOTTOM] = _bottom;
	trySides();
	current = make_unique<RandomParalellogram>(RandomParalellogram());
	current->getMonochrome(*this);
}

Parallelogram::Parallelogram(const Parallelogram& _Right):
	resistibility(_Right.resistibility)
{
	for (unsigned short i = 0;i < sides;++i)
	{
		piece[i] = _Right.piece[i];
	}
	current = make_unique<RandomParalellogram>(RandomParalellogram());
	current->getMonochrome(*this);
}

Parallelogram::Parallelogram(bool) :
	resistibility(0)
{
	for (unsigned short i = 0;i < sides;++i)
	{
		Lego fill;
		fill.type = rand() % colors;
		fill.lenght = rand() % (max_lenght)+1;
		piece[i] = fill;
	}
	piece[TOP].lenght = piece[BOTTOM].lenght;
	piece[LEFT].lenght = piece[RIGHT].lenght;
	current = make_unique<RandomParalellogram>(RandomParalellogram());
	current->getMonochrome(*this);
}


unsigned short Parallelogram::getPredominantColor() const
{
	unsigned short types[colors] = { 0,0,0 };//counts
	for (int i = 0;i < sides;++i)
	{
		++types[piece[i].type];
	}
	return distance(types, max_element(types, types + colors));
}

void Parallelogram::getState() const
{
	
}

void Parallelogram::tryMonohrome()
{
	if (isMonochrome())
	{
        throw "Shape is already monochrome";
	}
	++resistibility;
	unsigned short predominant_color = getPredominantColor();
	for (unsigned short i = 0;i < sides; ++i)
	{
		if (piece[i].type != predominant_color)
		{
			piece[i].type = rand() % colors;
		}
	}
	
	current->getMonochrome(*this);
}

Parallelogram& Parallelogram::operator=(const Parallelogram& _Right)
{
	if (&_Right != this)
	{
		for (unsigned short i = 0;i < sides;++i)
		{
			piece[i] = _Right.piece[i];
		}
		current.reset();
		current = make_unique<RandomParalellogram>(RandomParalellogram());
		current->getMonochrome(*this);
	}
	return *this;
}

bool Parallelogram::getType() const
{
	return current->isMonochrome();
}

Lego Parallelogram::getPiece(unsigned short index) const
{
	if (index >= sides)
	{
        throw "Bad index";
	}
	return piece[index];
}

unsigned int Parallelogram::getResistibility() const
{
	return resistibility;
}

bool Parallelogram::isMonochrome() const
{
	return all_of((piece), piece+(sides), [=](Lego val) { return val.type == piece[0].type; });
}

void Parallelogram::trySides() const
{
	if (piece[RIGHT].lenght != piece[LEFT].lenght || piece[TOP].lenght != piece[BOTTOM].lenght)
	{
        throw "Incorrect parallelogram";
	}
}

/*void Parallelogram::copyState(unique_ptr<Parallelogram::BaseState>& _Right)
{
	if (typeid(*_Right) == typeid(Parallelogram::Monochrome))
	{
		current.reset();
		current = make_unique<BaseState>(Monochrome());
	}
	else
	{
		current.reset();
		current = make_unique<BaseState>(RandomParalellogram());
	}
}*/

ostream & operator<<(ostream& stream, const Parallelogram& output)
{
	for (unsigned short i = 0;i < sides; ++i)
	{
		stream << "Side #" << i << ": " << output.piece[i] << endl;
	}
	return stream << "\tResistibility: " << output.resistibility << "\tType: " << boolalpha << output.getType();
}

istream & operator>>(istream& stream, Parallelogram& input)
{
	for (unsigned short i = 0;i < sides;++i)
	{
		stream >> input.piece[i];
	}
	return stream;
}
