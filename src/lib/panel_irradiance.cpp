#include "panel_irradiance.h"

const double panel_irradiance::compute_S(
    const pv_sun::position_in_sky* pos,
    double L_rad,
    double beta_rad,
    double Z_S_rad,
    double n_refraction_index, 
    double thickness, 
    double K,
	double a0,
	double a1,
	double a2,
	double a3,
	double a4
) {

    double cos_theta = compute_cos_theta(L_rad, beta_rad, Z_S_rad, pos->delta_rad, pos->h_rad);
    double R_B = compute_R_B(cos_theta, pos->cos_Phi);
    double M = compute_M(pos->m, a0, a1, a2, a3, a4);
    double theta_r = compute_theta_r(acos(cos_theta), n_refraction_index);
    double taualpha_B = compute_taualpha_B(K, thickness, theta_r, acos(cos_theta));
    double taualpha_n = compute_taualpha_n(K, thickness, n_refraction_index);
    double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n);
    //double S = compute_S(taualpha_n, M, G_B, R_B, K_theta_B); //Eq. 12n
    double S = 1;
    return S;

}





