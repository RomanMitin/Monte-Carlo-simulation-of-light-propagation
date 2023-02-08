#include <random>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <thread>
#include <vector>

#include "Input.hpp"
#include "State.h"


constexpr int tab_size = 12;

void print_A_z(const std::vector<double>& a_z, double dz)
{
	std::cout << "A_z:\n";

	for (double z = 0; z < dz * a_z.size(); z += dz)
	{
		std::cout << z << std::setw(tab_size);
	}

	std::cout << '\n';


	for (int i = 0; i < a_z.size(); i++)
	{
		std::cout << a_z[i] << std::setw(tab_size);
	}
	std::cout << "\n\n";
}


void print_A_l(const std::vector<double>& a_l, double dr)
{
	std::cout << "A_l:\n";

	for (double r = 0; r < dr * a_l.size(); r += dr)
	{
		std::cout << r << std::setw(tab_size);
	}
	std::cout << '\n';

	for (int i = 0; i < a_l.size(); i++)
	{
		std::cout << a_l[i] << std::setw(tab_size);
	}
	std::cout << "\n\n";

}

void print_2D_arr(const Array_2d_t<double>& arr, double dr, double dz)
{
	std::cout << "A_rz:\nz\\r" << std::setw(tab_size);

	for (double r = 0; r < dr * arr.size_r(); r += dr)
	{
		std::cout << r << std::setw(tab_size);
	}

	std::cout << '\n';

	double z = 0.0;
	for (int i = 0; i < arr.size_c(); i++, z += dz)
	{
		std::cout << z << std::setw(tab_size);
		for (int j = 0; j < arr.size_r(); j++)
		{
			std::cout << arr[j][i] << std::setw(tab_size);
		}
		std::cout << '\n';
	}
}

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
		state.out[0].Rsp += state.out[i].Rsp;
		for (int j = 0; j < state.out[0].A_rz.size_c(); j++)
		{
			for (int k = 0; k < state.out[0].A_rz.size_r(); k++)
			{
				state.out[0].A_rz[j][k] += state.out[i].A_rz[j][k];
			}
		}
	}
}

int main(int argc, char* argv[])
{
	std::string input_str;
	if (argc >= 2)
		input_str = argv[1];
	else
		input_str = "../input/input.json";

	State_t s = input_state(input_str);

	const Output_t& out = s.out[0];
	const Array_2d_t<double>& arr = out.A_rz;

	execute_photon_launch(s);

	//std::cout << std::setprecision(3);
	std::cout << std::fixed;
	std::cout << std::setprecision(3);

	//print_A_l(a_l, s.dr);
	//print_A_z(a_z, s.dz);
	

	print_2D_arr(arr, s.dr, s.dz);

	std::cout << "\nDone!\n";


	return 0;
}