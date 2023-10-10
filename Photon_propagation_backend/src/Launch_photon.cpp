
#include "Launch_photon.hpp"
#include <thread>
#include <atomic>
#include <iostream>
#include <latch>
#include <chrono>

enum class cacl_state_e
{
	none, start_caclulation, finish_threads
};

void execute_photon_launch(State_t &state)
{
	std::atomic_uint64_t photon_launched = 0;

	std::atomic<cacl_state_e> cacl_state = cacl_state_e::none;
	std::latch simulatuin_end_latch{state.get_num_threads()};

	auto thread_routine = [&](int id)
	{
		while(cacl_state.load(std::memory_order_relaxed) != cacl_state_e::start_caclulation)
			{}

		tid = id;

		uint32_t num_threads = state.get_num_threads();
		int64_t iter_num = (state.photon_num + num_threads - 1) / num_threads;

		int64_t i = 0;
#ifdef WINDOWS
		constexpr int64_t block_size = (int64_t)2e+4;
		int64_t block_num = iter_num / block_size;

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
#endif
		for (; i < iter_num; i++)
			state.launch_photon();

		simulatuin_end_latch.arrive_and_wait();
	};

	std::vector<std::thread> threads;

	for (uint32_t i = 0; i < state.get_num_threads(); i++)
	{
		threads.emplace_back(thread_routine, i);
	}

	const auto start = std::chrono::steady_clock::now();
	cacl_state.store(cacl_state_e::start_caclulation ,std::memory_order_relaxed);
	simulatuin_end_latch.wait();
	auto end = std::chrono::steady_clock::now();
	// const std::chrono::duration<double> elapsed_seconds{end - start};

	std::cout << "Simulation time: " << std::chrono::duration<double>(end - start) << "\n";

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

	end = std::chrono::steady_clock::now();
	std::cout << "Total calculation time: " << std::chrono::duration<double>(end - start) << "\n";

	for (uint32_t i = 0; i < state.get_num_threads(); i++)
	{
		threads[i].join();
	}
}