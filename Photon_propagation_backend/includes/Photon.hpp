#pragma once

#include <cinttypes>

#include "Defines.hpp"
#include "Layer.hpp"

struct Rand_gen_t;

struct Photon_t
{
	double x, y, z; // point
	double ux, uy, uz; // direction

	uint32_t cur_layer_ind;

	double weight;

	bool dead;
	double step;
	double step_left;

	Photon_t() = delete;
	Photon_t(double Rspecular);

	bool is_alive();

	void Roulette(double rand_num);

	double spinTheta(double g, double rand_num);
	void spin(double g, double rand_num);

	void set_step_size_in_glass(const Layer_t& layer);
	void set_step_size_in_tissue(const Layer_t& layer, Rand_gen_t& rand_gen);

	//void set_step_size(const Layer_t& layer);
	
	bool hit_boundary(const Layer_t& layer);


	void do_step();

	~Photon_t() = default;
};