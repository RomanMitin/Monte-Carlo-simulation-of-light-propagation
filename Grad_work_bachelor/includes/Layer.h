#pragma once


struct Layer_t {
	double z0, z1; 
	double n; 
	double mua; 
	double mus; 
	double g; 
	double cos_crit0, cos_crit1;

	Layer_t() = default;

	bool is_glass() const;

	double Rspecular();

	~Layer_t() = default;
};

