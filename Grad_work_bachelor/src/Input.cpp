
#include <fstream>
#include <iostream>

#include <json.hpp>

#include "Input.hpp"


using json = nlohmann::json;


void from_json(const json& j, Layer_t& layer)
{
	layer.z0 = j.at("z0");
	layer.z1 = j.at("z1");

	//layer.n = j.at("n");

	layer.mua = j.at("mua");
	layer.mus = j.at("mus");

	layer.g = j.at("g");

	/*layer.cos_crit0 = j.at("cos_crit0");
	layer.cos_crit1 = j.at("cos_crit1");*/
}

void from_json(const json& j, State_t& state) 
{
	state.layers = j.at("layers");

	

	state.dz = j.at("dz");
	state.dr = j.at("dr");

	state.nz = j.at("nz");
	state.nr = j.at("nr");

	state.out.A_rz = Array_2d_t<double>(state.nr, state.nz);
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

	std::cout << j << '\n';


	state = j["State"];
	 
	return state;
}