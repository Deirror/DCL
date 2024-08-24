#include "capcal.h"
#include <tydefuint_t.h>

DCL_BEGIN

size_t upper_power_of_two(size_t number)
{
	ushort times = 3;

	while (number > (static_cast<size_t>(1) << times)) {
		times++;
	}

	return (static_cast<size_t>(1) << times);
}

DCL_END
