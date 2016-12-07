#include "Lego.h"



Lego::Lego()
{
}

Lego::Lego(unsigned short _type, unsigned short _lenght):
	type(_type),
	lenght(_lenght)
{
	if (lenght > max_lenght)
	{
        //throw exception("Exceeded max lenght", 3);
	}
}


Lego::~Lego()
{
}

ostream& operator<<(ostream& stream, const Lego& output)
{
	return stream << "Color: " << colors_text[output.type] << "\t Lenght: " <<  output.lenght;
}

istream & operator>>(istream& stream, Lego& input)
{
	return stream >> input.type >> input.lenght;
}
