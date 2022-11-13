#include <random>
#include <iostream>
#include <unordered_map>
#include <iomanip>

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

int main(int argc, char* argv[])
{
	std::string input_str;
	if (argc >= 2)
		input_str = argv[1];
	else
		input_str = "../input/input.json";

	State_t s = input_state(input_str);

	const Output_t& out = s.out;
	const Array_2d_t<double>& arr = out.A_rz;

	for (int i = 0; i < 500'000; i++)
		s.launch_photon();

	//std::cout << std::setprecision(3);
	std::cout << std::fixed;
	std::cout << std::setprecision(3);

	//print_A_l(a_l, s.dr);
	//print_A_z(a_z, s.dz);
	

	print_2D_arr(arr, s.dr, s.dz);

	std::cout << "\nDone!\n";


	return 0;
}