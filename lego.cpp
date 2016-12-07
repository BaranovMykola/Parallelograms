#include "Lego.h"




Lego::Lego(unsigned short _type, unsigned short _lenght):
	type(_type),
	lenght(_lenght)
{
	if (lenght > max_lenght)
	{
        throw "Exceeded max lenght";
	}
}

ostream& operator<<(ostream& stream, const Lego& output)
{
	return stream << "Color: " << colors_text[output.type] << "\t Lenght: " <<  output.lenght;
}

istream & operator>>(istream& stream, Lego& input)
{
	return stream >> input.type >> input.lenght;
}
