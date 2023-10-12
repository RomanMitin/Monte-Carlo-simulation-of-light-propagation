#pragma once

#include <cinttypes>
#include <random>


class Rand_gen_t
{
	// TODO add align
	std::vector<std::mt19937> rand_engines;
public:
	Rand_gen_t(size_t num_threads = 1);

	void set_thread_num(size_t new_thread_num);
	Rand_gen_t(Rand_gen_t&&) = default;

	// Rand_gen_t(uint32_t seed);

	Rand_gen_t& operator=(Rand_gen_t&&) = default;

	double operator()(int tid);

	~Rand_gen_t() = default;
};