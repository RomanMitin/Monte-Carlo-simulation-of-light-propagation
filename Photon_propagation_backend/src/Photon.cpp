#include "Photon.hpp"
#include "Rand_gen.hpp"
#include "State.hpp"

#include <cmath>
#include <assert.h>

static double get_sign(double num)
{
	uint64_t bit_num = static_cast<uint64_t>(num);
	bit_num &= (1ull << 63);

	return bit_num ? -1.0 : 1.0;
}

Photon_t::Photon_t(double Rspecular)
	:x(), y(), z(), ux(), uy(), uz(1.0), cur_layer_ind(1), 
		weight(1.0 - Rspecular), dead(), step(), step_left()
{

}

bool Photon_t::is_alive()
{
	return !dead;
}

void Photon_t::Roulette(double rand_num)
{
	assert(weight >= 0);

	if (weight == 0)
	{
		dead = true;
	}
	else
	{
		if (rand_num < CHANCE)
		{
			weight /= CHANCE;
		}
		else
		{
			dead = true;
		}
	}
}

double Photon_t::spinTheta(double g, double rand_num)
{
	double cost;

	if (g == 0.0)
	{
		cost = 2 * rand_num - 1;
	}
	else 
	{
		double temp = (1 - g * g) / (1 - g + 2 * g * rand_num);
		cost = (1 + g * g - temp * temp) / (2 * g);

	}

	return cost;
}

void Photon_t::spin(double g, double rand_num)
{

	double cost, sint; /* cosine and sine of the */
	 /* polar deflection angle theta. */
	double cosp, sinp; /* cosine and sine of the */
	/* azimuthal angle psi. */
	double psi;

	cost = spinTheta(g, rand_num);
	sint = sqrt(1.0 - cost * cost);
	/* sqrt() is faster than sin(). */

	psi = 2.0 * PI * rand_num; /* spin psi 0-2pi. */
	cosp = cos(psi);
	if (psi < PI)
		sinp = sqrt(1.0 - cosp * cosp);
	/* sqrt() is faster than sin(). */
	else
		sinp = -sqrt(1.0 - cosp * cosp);

	if (fabs(uz) > COS0)
	{ /* normal incident. */
		ux = sint * cosp;
		uy = sint * sinp;
		uz = cost * get_sign(uz);
		/* SIGN() is faster than division. */
	}
	else
	{ /* regular incident. */
		double temp = sqrt(1.0 - uz * uz);
		ux = sint * (ux * uz * cosp - uy * sinp) / temp + ux * cost;
		uy = sint * (uy * uz * cosp + ux * sinp) / temp + uy * cost;
		uz = -sint * cosp * temp + uz * cost;
	}

}

void Photon_t::set_step_size_in_glass(const Layer_t& layer)
{
	if (uz > 0.0)
		step = (layer.z1 - z) / uz;
	else
		if (uz < 0.0)
			step = (layer.z0 - z) / uz;
		else
			step = 0.0;
}

void Photon_t::set_step_size_in_tissue(const Layer_t& layer, Rand_gen_t& rand_gen)
{
	double mut = layer.mua + layer.mus;

	if (step_left == 0.0) {

		double rnd;
		do
		{
			rnd = rand_gen(tid);
		}
		while (rnd == 0.0);

		step = -log(rnd) / mut;
	}
	else
	{ 
		step = step_left / mut;
		step_left = 0.0;
	}
}

bool Photon_t::hit_boundary(const Layer_t& layer)
{
	double dl_b; /* length to boundary. */
	bool hit = false;

	if (uz != 0.0)
	{
		/* Distance to the boundary. */
		if (uz > 0.0)
			dl_b = (layer.z1 - z) / uz;
		else
			dl_b = (layer.z0 - z) / uz;

		if (step > dl_b)
		{
			/* not horizontal & crossing. */
			double mut = layer.mua + layer.mus;

			step_left = (step - dl_b) * mut;
			step = dl_b;
			hit = true;
		}
	}

	return hit;
}

void Photon_t::do_step()
{
	x += step * ux;
	y += step * uy;
	z += step * uz;
}