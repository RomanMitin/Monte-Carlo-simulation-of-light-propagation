#pragma once
#include <vector>
#include <cinttypes>
#include "Array_2D.h"

struct Output_t
{
	double Rsp; /* specular reflectance. [-] */
	Array_2d_t<double> Rd_ra; /* 2D distribution of diffuse */
	/* reflectance. [1/(cm2 sr)] */
	std::vector<double> Rd_r; /* 1D radial distribution of diffuse */
	/* reflectance. [1/cm2] */
	std::vector<double> Rd_a; /* 1D angular distribution of diffuse */
	/* reflectance. [1/sr] */
	double Rd; /* total diffuse reflectance. [-] */
	Array_2d_t<double> A_rz; /* 2D probability density in turbid */
	/* media over r & z. [1/cm3] */
	std::vector<double> A_z; /* 1D probability density over z. */
	/* [1/cm] */
	std::vector<double> A_l; /* each layer's absorption */
		/* probability. [-] */
	double A; /* total absorption probability. [-] */
	Array_2d_t<double> Tt_ra; /* 2D distribution of total */
	/* transmittance. [1/(cm2 sr)] */
	std::vector<double> Tt_r; /* 1D radial distribution of */
	/* transmittance. [1/cm2] */
	std::vector<double> Tt_a; /* 1D angular distribution of */
	/* transmittance. [1/sr] */
	double Tt; /* total transmittance. [-] */

};

