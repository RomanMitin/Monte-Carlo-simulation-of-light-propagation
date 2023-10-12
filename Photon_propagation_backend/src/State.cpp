
#include <assert.h>
#include <algorithm>

#include "State.hpp"
#include "Rand_gen.hpp"

extern Rand_gen_t rand_gen;

double RFresnel(double n1, double n2, double ca1, double* ca2_Ptr);

Layer_t& State_t::get_layer(Photon_t& photon)
{
	assert(photon.cur_layer_ind < layers.size());
	return layers[photon.cur_layer_ind];
}

// RecordR //
void State_t::update_weight(Photon_t& photon) 
{
	double dwa; /* absorbed weight.*/
	double x = photon.x;
	double y = photon.y;
	uint32_t iz, ir; /* index to z & r. */
	const Layer_t& layer = get_layer(photon);
	double mua, mus;
	
	/* update photon weight. */
	mua = layer.mua;
	mus = layer.mus;
	dwa = photon.weight * mua / (mua + mus);
	photon.weight -= dwa;

	/* compute array indices. */
	iz = static_cast<uint32_t>(photon.z / dz);
	//iz = std::min(iz, nz - 1);
	if (iz >= nz)
	{
		return;
	}

	ir = static_cast<uint32_t>(sqrt(x * x + y * y) / dr);
	if (ir >= nr)
	{
		return;
	}


	/* assign dwa to the absorption array element. */
	Output_data[tid].A_rz[ir][iz] += dwa;
	//Output_data.A_z[iz] += dwa;
	//Output_data.A_l[ir] += dwa;
	Output_data[tid].A += dwa;
}

void State_t::update_A_rz(Photon_t& photon)
{
	update_weight(photon);
}

//void State_t::update_Rd_r(double ref1, Photon_t& photon)
//{
//	double x = photon.x;
//	double y = photon.y;
//	uint32_t ir, ia; /* index to r & angle. */
//
//	ir = static_cast<uint32_t>(sqrt(x * x + y * y) / dr);
//	ir = std::max(ir, nr - 1);
//
//	ia = static_cast<uint32_t>(acos(-photon.uz) / da);
//	ir = std::max(ir, nr - 1);
//
//	/* assign photon to the transmittance array element. */
//	//Output_data.Rd_ra[ir][ia] += photon.weight * (1.0 - ref1);
//
//	photon.weight *= ref1;
//
//}

//void State_t::update_T_ra(double ref1, Photon_t& photon)
//{
//	double x = photon.x;
//	double y = photon.y;
//	uint32_t ir, ia; /* index to r & angle. */
//
//	ir = static_cast<uint32_t>(sqrt(x * x + y * y) / dr);
//	ir = std::max(ir, nr - 1);
//
//	ia = static_cast<uint32_t>(acos(photon.uz) / da);
//	ir = std::max(ir, nr - 1);
//
//	/* assign photon to the transmittance array element. */
//	//Output_data.Tt_ra[ir][ia] += photon.weight * (1.0 - ref1);
//
//	photon.weight *= ref1;
//}

void State_t::try_cross(Photon_t& photon)
{
	double uz = photon.uz; /* z directional cosine. */

	bool is_up_cross = uz > 0.0 ? false : true;
	int sign = is_up_cross ? -1 : 1;

	double uz1 = 0.0; /* cosines of transmission alpha. */
	double r = 0.0; /* reflectance */
	const Layer_t& layer = layers[photon.cur_layer_ind];
	const Layer_t& next_layer = layers[photon.cur_layer_ind + sign];

	double ni = layer.n;
	double nt = next_layer.n;

	/* Get r. */
	if (is_up_cross)
	{
		if (-uz <= layer.cos_crit0)
			r = 1.0; /* total internal reflection. */
		else
			r = RFresnel(ni, nt, -uz, &uz1);
	}
	else
	{
		if (uz <= layer.cos_crit1)
			r = 1.0; /* total internal reflection. */
		else
			r = RFresnel(ni, nt, uz, &uz1);
	}
	
	size_t limit = is_up_cross ? 1 : layers.size() - 2;

	if constexpr (PARTIAL_REFLECTION)
	{
		if (photon.cur_layer_ind == limit && r < 1.0) 
		{
			//photon.uz = -uz1;
			//if (is_up_cross)
			//	//update_Rd_r(r, photon);
			//else
			//	//update_T_ra(r, photon);
			photon.uz = -uz;
		}
		else
			if (rand_gen(tid) > r)
			{/* transmitted to layer+1. */
				photon.cur_layer_ind += sign;
				photon.ux *= ni / nt;
				photon.uy *= ni / nt;
				photon.uz = sign * uz1;

			}
			else /* reflected. */
				photon.uz = -uz;
	}
	else
	{
		
		if (rand_gen(tid) > r) 
		{ 
			/* transmitted to layer+1. */
			if (photon.cur_layer_ind == limit) {
				photon.uz = uz1;
				//if (is_up_cross)
				//	//update_Rd_r(r, photon);
				//else
				//	//update_T_ra(0.0, photon);
				photon.dead = true;
			}
			else 
			{
				photon.cur_layer_ind += sign;
				photon.ux *= ni / nt;
				photon.uy *= ni / nt;
				photon.uz = sign * uz1;
			}

		}
		else /* reflected. */
			photon.uz = -uz;
	}

}

void State_t::alg_step_glass(Photon_t& photon)
{
	const Layer_t& layer = get_layer(photon);

	if (photon.uz == 0.0)
	{
		photon.dead = true;
	}
	else 
	{
		photon.set_step_size_in_glass(layer);
		photon.do_step();
		try_cross(photon);
	}
}

void State_t::alg_step_tissue(Photon_t& photon)
{
	const Layer_t& layer = get_layer(photon);

	photon.set_step_size_in_tissue(layer, rand_gen);

	if (photon.hit_boundary(layer))
	{
		photon.do_step();
		try_cross(photon);
	}
	else
	{
		photon.do_step();
		update_weight(photon);
		photon.spin(layer.g, rand_gen(tid));
	}
}

void State_t::alg_step(Photon_t& photon)
{
	const Layer_t& cur_layer = get_layer(photon);

	if (cur_layer.is_glass())
	{
		alg_step_glass(photon);
	}
	else
	{
		alg_step_tissue(photon);
	}

	if (photon.weight < critical_weigth && photon.is_alive())
	{
		photon.Roulette(rand_gen(tid));
	}

}

void State_t::launch_photon()
{
	Photon_t photon{ Output_data[tid].Rsp};

	while (photon.is_alive())
		alg_step(photon);
}

void State_t::calc_Rspecular()
{
	assert(layers.size() >= 2);

	double r1, r2;
	double temp;

	temp = (layers[0].n - layers[1].n) / (layers[0].n + layers[1].n);
	r1 = temp * temp;

	if (layers[1].is_glass() && layers.size() >= 3)
	{ 
		temp = (layers[1].n - layers[2].n) / (layers[1].n + layers[2].n);
		r2 = temp * temp;
		r1 = r1 + (1 - r1) * (1 - r1) * r2 / (1 - r1 * r2);
	}

	Output_data[tid].Rsp = r1;
}

uint32_t State_t::get_num_threads()
{
	return Output_data.size();
}



double RFresnel(double n1, double n2, double ca1, double* ca2_Ptr)
{
	double r;

	if (n1 == n2)
	{ /** matched boundary. **/
		*ca2_Ptr = ca1;
		r = 0.0;
	}
	else if (ca1 > COS0)
	{ /** normal incident. **/
		*ca2_Ptr = ca1;
		r = (n2 - n1) / (n2 + n1);
		r *= r;
	}
	else if (ca1 < COS90)
	{ /** very slant. **/
		*ca2_Ptr = 0.0;
		r = 1.0;
	}
	else
	{ /** general. **/
		double sa1, sa2;
		/* sine of the incident and transmission angles. */
		double ca2;

		sa1 = sqrt(1 - ca1 * ca1);
		sa2 = n1 * sa1 / n2;
		if (sa2 >= 1.0) {
			/* double check for total internal reflection. */
			*ca2_Ptr = 0.0;
			r = 1.0;

		}
		else
		{
			double cap, cam; /* cosines of the sum ap or */
			/* difference am of the two */
				/* angles. ap = a1+a2 */
				/* am = a1 - a2. */
			double sap, sam; /* sines. */

			*ca2_Ptr = ca2 = sqrt(1 - sa2 * sa2);

			cap = ca1 * ca2 - sa1 * sa2; /* c+ = cc - ss. */
			cam = ca1 * ca2 + sa1 * sa2; /* c- = cc + ss. */
			sap = sa1 * ca2 + ca1 * sa2; /* s+ = sc + cs. */
			sam = sa1 * ca2 - ca1 * sa2; /* s- = sc - cs. */
			r = 0.5 * sam * sam * (cam * cam + cap * cap) / (sap * sap * cam * cam);
			/* rearranged for speed. */

		}
	}

	return r;
}