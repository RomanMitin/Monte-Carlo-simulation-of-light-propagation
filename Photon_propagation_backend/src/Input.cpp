
#include <fstream>
#include <iostream>

#include <json.hpp>

#include "Input.hpp"


using json = nlohmann::json;

void handle_json_exception(const json::exception& ex)
{
	std::cerr << "Exception in json file!!\n";
	std::cerr << ex.what();
}

void from_json(const json& j, Layer_t& layer)
{
	try
	{
		layer.z0 = j.at("z0");
		layer.z1 = j.at("z1");

		layer.n = j.at("n");

		layer.mua = j.at("mua");
		layer.mus = j.at("mus");

		layer.g = j.at("g");
	}
	catch (json::exception ex)
	{
		handle_json_exception(ex);
	}
	/*layer.cos_crit0 = j.at("cos_crit0");
	layer.cos_crit1 = j.at("cos_crit1");*/
}

void calc_cos_crit(std::vector<Layer_t>& layers)
{
	size_t i;
	double n1, n2;

	for (i = 1; i < layers.size() - 1; i++)
	{
		n1 = layers[i].n;
		n2 = layers[i - 1].n;
		layers[i].cos_crit0 = n1 > n2 ? sqrt(1.0 - n2 * n2 / (n1 * n1)) : 0.0;

		n2 = layers[i + 1].n;
		layers[i].cos_crit1 = n1 > n2 ? sqrt(1.0 - n2 * n2 / (n1 * n1)) : 0.0;
	}

	n1 = layers[i].n;
	n2 = layers[i - 1].n;
	layers[i].cos_crit0 = n1 > n2 ? sqrt(1.0 - n2 * n2 / (n1 * n1)) : 0.0;
}

void from_json(const json& j, State_t& state)
{
	std::vector<Layer_t> tmp_vec;

	try
	{

		tmp_vec = j.at("layers");
	}
	catch (json::exception ex)
	{
		handle_json_exception(ex);
	}

	state.layers.emplace_back(Layer_t());
	std::copy(tmp_vec.begin(), tmp_vec.end(), std::back_inserter(state.layers));
	state.layers.emplace_back(Layer_t(state.layers.back().z1));

	try
	{
		state.dz = j.at("dz");
		state.dr = j.at("dr");
	}
	catch (json::exception ex)
	{
		handle_json_exception(ex);
	}

	double lenght_r = j.at("lenght_r");
	state.nr = (lenght_r + state.dr - 1) / state.dr;
	state.nz = static_cast<uint32_t>(state.layers.back().z0 / state.dz);

	//state.Output_data.A_l.resize(state.nr);
	//state.Output_data.A_z.resize(state.nz);
	if (j.find("nz") != j.end())
	{
		std::cerr << "Warning: nz not uzed\n";
	}

	uint32_t thread_num;
	try
	{
		state.critical_weigth = j.at("Critical_weight");
		state.photon_num = j.at("Photon_num");
		thread_num = j.at("Thread_num");
	}
	catch (json::exception ex)
	{
		handle_json_exception(ex);
	}

	state.Output_data.resize(thread_num);

	for (uint32_t i = 0; i < thread_num; i++)
	{
		state.Output_data[i].A_rz = Array_2d_t<double>(state.nr, state.nz);
	}
}

State_t input_state(const std::string& input_file_name)
{
	std::ifstream input(input_file_name);

	if (!input.is_open())
	{
		std::cerr << "Can not open input file: " << input_file_name << '\n';
		exit(1);
	}

	State_t state;

	json j = json::parse(input);

	input.close();

	//std::cout << j << '\n';

	try
	{
		state = j.at("State");
	}
	catch (json::exception ex)
	{
		handle_json_exception(ex);
	}

	calc_cos_crit(state.layers);
	state.calc_Rspecular();

	return state;
}