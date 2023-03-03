#include <iostream>
#include <iomanip>

#include "Input.hpp"
#include "Output_to_console.hpp"
#include "Output_to_file.hpp"
#include "Launch_photon.hpp"



int main(int argc, char* argv[])
{
	std::string input_str;
	if (argc >= 2)
		input_str = argv[1];
	else
		input_str = "D:\\Code\\Monte-Carlo-simulation-of-light-propagation\\input\\input.json";

	State_t s = input_state(input_str);

	const Output_data_t& Output_data = s.Output_data[0];
	const Array_2d_t<double>& arr = Output_data.A_rz;

	execute_photon_launch(s);

	std::string output_str;
	if (argc >= 3)
	{
		output_str = argv[2];
		output_to_file(Output_data, output_str);
	}
	else
	{
		//std::cout << std::setprecision(3);
		std::cout << std::fixed;
		std::cout << std::setprecision(3);

		//print_A_l(a_l, s.dr);
		//print_A_z(a_z, s.dz);


		print_2D_arr(arr, s.dr, s.dz);

		std::cout << "\nDone!\n";
	}

	


	return 0;
}