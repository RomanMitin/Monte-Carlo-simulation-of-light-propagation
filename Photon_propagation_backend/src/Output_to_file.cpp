#include "Output_to_file.hpp"
#include <iostream>
#include <fstream>

void output_to_file(const Output_data_t& output_data, const std::string& output_filename)
{
	std::ofstream output_file;

	output_file.open(output_filename, std::ios_base::binary);

	if (!output_file.is_open())
	{
		std::cerr << "Cant open outfile\n";
		exit(9);
	}

	const Array_2d_t<double>& output_array = output_data.A_rz;

	size_t size_r = output_array.size_r();
	size_t size_c = output_array.size_c();

	char* data = reinterpret_cast<char*>(output_array.data);

	output_file.write((char*)&size_c, sizeof(size_t));
	output_file.write((char*)&size_r, sizeof(size_t));

	output_file.write(data, size_r * size_c * sizeof(double));

	output_file.close();
}