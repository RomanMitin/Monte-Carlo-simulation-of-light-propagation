#include "Layer.h"

bool Layer_t::is_glass() const
{
	return mua == 0 && mus == 0;
}