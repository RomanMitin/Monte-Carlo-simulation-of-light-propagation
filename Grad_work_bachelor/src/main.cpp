#include <random>
#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "Input.hpp"
#include "State.h"


void print_A_z(const std::vector<double>& a_z, double dz)
{
	std::cout << "A_z:\n";

	for (double z = 0; z < dz * a_z.size(); z += dz)
	{
		std::cout << z << '\t';
	}

	std::cout << '\n';


	for (int i = 0; i < a_z.size(); i++)
	{
		std::cout << a_z[i] << '\t';
	}
	std::cout << "\n\n";
}


void print_A_l(const std::vector<double>& a_l, double dr)
{
	std::cout << "A_l:\n";

	for (double r = 0; r < dr * a_l.size(); r += dr)
	{
		std::cout << r << '\t';
	}
	std::cout << '\n';

	for (int i = 0; i < a_l.size(); i++)
	{
		std::cout << a_l[i] << '\t';
	}
	std::cout << "\n\n";

}

void print_2D_arr(const Array_2d_t<double>& arr, double dr, double dz)
{
	std::cout << "A_rz:\nz\\r\t";

	for (double r = 0; r < dr * arr.size_r(); r += dr)
	{
		std::cout << r << '\t';
	}

	std::cout << '\n';

	double z = 0.0;
	for (int i = 0; i < arr.size_r(); i++, z += dz)
	{
		std::cout << z << '\t';
		for (int j = 0; j < arr.size_c(); j++)
		{
			std::cout << arr[i][j] << '\t';
		}
		std::cout << '\n';
	}
}

int main()
{
	State_t s = input_state();

	const Output_t& out = s.out;
	const Array_2d_t<double>& arr = out.A_rz;
	const std::vector<double>& a_l = out.A_l;
	const std::vector<double>& a_z = out.A_z;

	for (int i = 0; i < 1'000; i++)
		s.launch_photon();

	std::cout << std::setprecision(4);

	print_A_l(a_l, s.dr);
	print_A_z(a_z, s.dz);
	

	print_2D_arr(arr, s.dr, s.dz);

	std::cout << "\nDone!\n";


	return 0;
}