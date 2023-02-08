#pragma once

#include <vector>
#include <cinttypes>

#include "Output.h"
#include "Rand_gen.h"
#include "Layer.h"
#include "Photon.h"

struct State_t
{
	uint64_t photon_num;

	std::vector<Layer_t> layers;

	//Rand_gen_t rand_gen;

	double dz, dr/*, da*/;

	double critical_weigth;

	uint32_t nz, nr/*, na*/;
	std::vector<Output_t> out;

	State_t() = default;

	Layer_t& get_layer(Photon_t& photon);

	void update_weight(Photon_t& photon);
	void update_A_rz(Photon_t& photon);
	//void update_Rd_r(double ref1, Photon_t& photon);
	//void update_T_ra(double ref1, Photon_t& photon);

	void try_cross(Photon_t& photon);

	void alg_step_glass(Photon_t& photon);
	void alg_step_tissue(Photon_t& photon);

	void alg_step(Photon_t& photon);
	void launch_photon();

	void calc_Rspecular();

	uint32_t get_num_threads();

	~State_t() = default;
};

inline thread_local int tid;