#include "Rand_gen.h"

Rand_gen_t::Rand_gen_t()
	:rand_engine(), dist() {}

Rand_gen_t::Rand_gen_t(const Rand_gen_t& rhs)
	: rand_engine(rhs.rand_engine), dist(rhs.dist) {}

Rand_gen_t::Rand_gen_t(uint32_t seed)
	: rand_engine(seed), dist() {}

Rand_gen_t& Rand_gen_t::operator=(const Rand_gen_t& rhs)
{
	rand_engine = rhs.rand_engine;
	dist = rhs.dist;

	return *this;
}

double Rand_gen_t::operator()()
{
	return dist(rand_engine);
}

