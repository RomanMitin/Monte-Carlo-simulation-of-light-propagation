
#include "Launch_photon.hpp"
#include <thread>
#include <atomic>
#include <iostream>

void execute_photon_launch(State_t& state)
{
	std::atomic_uint64_t photon_launched = 0;

	auto thread_routine = [&](int id)
	{
		tid = id;

		uint32_t num_threads = state.get_num_threads();
		int64_t iter_num = (state.photon_num + num_threads - 1) / num_threads;


		constexpr int64_t block_size = (int64_t)2e+4;

		int64_t block_num = iter_num / block_size;

		int64_t i = 0;
		for (int64_t block_id = 1; block_id <= block_num; block_id++)
		{
			for (; i < block_id * block_size; i++)
			{
				state.launch_photon();
			}

			uint64_t cur_photon_launched = photon_launched.fetch_add(block_size, std::memory_order_relaxed);
			if (tid == 0)
			{
				cur_photon_launched += block_size;
				std::cout << cur_photon_launched << std::endl;
			}
		}

		for (; i < iter_num; i++)
			state.launch_photon();
	};

	std::vector<std::thread> threads;

	for (uint32_t i = 0; i < state.get_num_threads(); i++)
	{
		threads.emplace_back(thread_routine, i);
	}

	for (uint32_t i = 0; i < state.get_num_threads(); i++)
	{
		threads[i].join();
	}

	for (uint32_t i = 1; i < state.get_num_threads(); i++)
	{
		state.Output_data[0].Rsp += state.Output_data[i].Rsp;
		for (size_t j = 0; j < state.Output_data[0].A_rz.size_r(); j++)
		{
			for (size_t k = 0; k < state.Output_data[0].A_rz.size_c(); k++)
			{
				state.Output_data[0].A_rz[j][k] += state.Output_data[i].A_rz[j][k];
			}
		}
	}
}