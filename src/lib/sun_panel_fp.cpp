#include "sun_panel_fp.h"
#include <iostream>


//DEPRECATA usare panel_irradiance

//Area 
pure double absorbed_radiation_S(
    const double L_rad,
    const pv_sun::position_in_sky pos,
    const double beta_rad,
    const double Z_S_rad
) {
	std::cout<<"sun_panel_fp deprecata, usare panel_irradiance::compute_S"<<std::endl;
	const double K = 4; // m^-1
	const double thickness = 0.002; // m la chiama L
	const double G_B = 715; // W/m^2
    const double n_refraction_index = 1.526;

	//Monocristallino Tabella pg. 514
	const double alpha_0 = 0.935823;
	const double alpha_1 = 0.054289;
	const double alpha_2 = -0.008677;
	const double alpha_3 = 0.000527;
	const double alpha_4 = -0.000011;

	const double cos_theta = compute_cos_theta(L_rad, beta_rad,
		Z_S_rad, pos.delta_rad, pos.h_rad); //Eq. 4
	const double theta = acos(cos_theta);

	const double R_B = compute_R_B(cos_theta, pos.cos_Phi); //Eq. 5n
	

	const double M = compute_M(pos.m, alpha_0, alpha_1,
		alpha_2, alpha_3, alpha_4); //Eq. 7n

	const double theta_r = compute_theta_r(theta, n_refraction_index); //Eq. 8n

	double taualpha_B = compute_taualpha_B(K, thickness, theta_r, theta); //Eq. 9n

	double taualpha_n = compute_taualpha_n(K, thickness,n_refraction_index); //Eq. 10n

	double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n); //Eq. 11n

	//double S = compute_S(taualpha_n, M, G_B, R_B, K_theta_B); //Eq. 12n
	double S = 1;
    /*
	std::cout << "TauAlpha_n: " << taualpha_n << std::endl
		<< "M: " << M << std::endl
		<< "G_B: " << G_B << std::endl
		<< "R_B: " << R_B << std::endl
		<< "K_theta_B: " << K_theta_B << std::endl
		<< "S: " << S << std::endl;
    */
    return S;

}

