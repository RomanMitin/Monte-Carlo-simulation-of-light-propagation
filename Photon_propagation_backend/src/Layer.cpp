#include "Layer.hpp"


Layer_t::Layer_t()
	: z0(1e-100), z1(), n(1.0), mua(), mus(),
	g(), cos_crit0(), cos_crit1()
{

}

Layer_t::Layer_t(double z0)
	: z0(z0), z1(1e+100), n(1.0), mua(), mus(),
	g(), cos_crit0(), cos_crit1()
{

}

bool Layer_t::is_glass() const
{
	return mua == 0 && mus == 0;
}