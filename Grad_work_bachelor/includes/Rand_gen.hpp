#pragma once

#include <cinttypes>
#include <random>


class Rand_gen_t
{
	std::mt19937 rand_engine;
	std::uniform_real_distribution<> dist;
public:
	Rand_gen_t();
	Rand_gen_t(const Rand_gen_t&);

	Rand_gen_t(uint32_t seed);

	Rand_gen_t& operator=(const Rand_gen_t&);

	double operator()();

	~Rand_gen_t() = default;
};