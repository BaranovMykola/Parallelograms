#include "MonochromeParallelogram.h"
#include <exception>

void MonochromeParallelogram::getMonochrome(Parallelogram &) const
{
    throw "Sharpe is already monochrome";
}

bool MonochromeParallelogram::isMonochrome() const
{
	return true;
}
