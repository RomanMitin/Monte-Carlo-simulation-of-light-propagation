#include <random>
#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "Input.hpp"
#include "State.h"


int main()
{
	State_t s = input_state();

	const Output_t& out = s.out;
	const Array_2d_t<double>& arr = out.A_rz;

	for (int i = 0; i < 100; i++)
		s.launch_photon();

	std::cout << std::setprecision(4);

	std::cout << "A_rz:\n\t";

	for (double r = 0; r < s.dr * arr.size_r(); r += s.dr)
	{
		std::cout << r << '\t';
	}

	std::cout << '\n';

	double z =0.0;
	for (int i = 0; i < arr.size_r(); i++, z += s.dz)
	{
		std::cout << z << '\t';
		for (int j = 0; j < arr.size_c(); j++)
		{
			std::cout << arr[i][j] << '\t';
		}
		std::cout << '\n';
	}

	std::cout << "\nDone!\n";


	return 0;
}