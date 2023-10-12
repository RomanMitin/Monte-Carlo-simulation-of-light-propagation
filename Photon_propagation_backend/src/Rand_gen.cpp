#include "Rand_gen.hpp"
#include <cassert>

Rand_gen_t::Rand_gen_t(size_t num_threads)
	: rand_engines()
{
	set_thread_num(num_threads);
}

void Rand_gen_t::set_thread_num(size_t new_thread_num)
{
	rand_engines.clear();
	rand_engines.reserve(new_thread_num);
	for (size_t i = 0; i < new_thread_num; i++)
	{
		rand_engines.emplace_back(i);
	}
}

double Rand_gen_t::operator()(int tid)
{
	assert(tid < rand_engines.size());
	std::uniform_real_distribution dist(0.0, 1.0);
	return dist(rand_engines[tid]);
}
