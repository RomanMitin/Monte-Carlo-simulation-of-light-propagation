#pragma once

#include <cinttypes>

#include "Defines.hpp"
#include "Layer.hpp"

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

	void Roulette();

	double spinTheta(double g);
	void spin(double g);

	void set_step_size_in_glass(const Layer_t& layer);
	void set_step_size_in_tissue(const Layer_t& layer);

	//void set_step_size(const Layer_t& layer);
	
	bool hit_boundary(const Layer_t& layer);


	void do_step();

	~Photon_t() = default;
};