
#include "Launch_photon.hpp"
#include <thread>

void execute_photon_launch(State_t& state)
{
	auto thread_routine = [&](int id)
	{
		tid = id;

		int num_threads = state.get_num_threads();
		int iter_num = (state.photon_num + num_threads - 1) / num_threads;


		for (int i = 0; i < iter_num; i++)
			state.launch_photon();
	};

	std::vector<std::thread> threads;

	for (int i = 0; i < state.get_num_threads(); i++)
	{
		threads.emplace_back(thread_routine, i);
	}

	for (int i = 0; i < state.get_num_threads(); i++)
	{
		threads[i].join();
	}

	for (int i = 1; i < state.get_num_threads(); i++)
	{
		state.Output_data[0].Rsp += state.Output_data[i].Rsp;
		for (int j = 0; j < state.Output_data[0].A_rz.size_r(); j++)
		{
			for (int k = 0; k < state.Output_data[0].A_rz.size_c(); k++)
			{
				state.Output_data[0].A_rz[j][k] += state.Output_data[i].A_rz[j][k];
			}
		}
	}
}