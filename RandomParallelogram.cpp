#include "RandomParallelogram.h"
#include "Parallelogram.h"
#include "MonochromeParallelogram.h"

void RandomParalellogram::getMonochrome(Parallelogram & _object) const
{
		if (_object.isMonochrome())
		{
			_object.current.reset();
			_object.current = make_unique<MonochromeParallelogram>(MonochromeParallelogram());
		}
}

bool RandomParalellogram::isMonochrome() const
{
	return false;
}
