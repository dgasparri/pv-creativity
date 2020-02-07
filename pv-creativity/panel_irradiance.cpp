#include "../../pv-creativity/src/lib/irradiance_fp.h"


const double panel_irradiance::compute_S(

	const pv_sun::position_in_sky* pos,

	int N,

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

	double a4,

	s_debug* debug_output

) {



	if (debug_output == nullptr) {

		debug_output = new panel_irradiance::s_debug;

	}



	double G_on = compute_G_on(N, G_SC_CONSTANT);

	double G_oH = compute_G_oH(G_on, pos->cos_Phi);



	double H_o_rad = compute_H_o_rad(L_rad, pos->delta_rad, pos->h_ss_rad, G_on);

	double H_o = compute_H_o(H_o_rad);

	double r_ground = compute_r_ground(N);

	double H = compute_H(H_o, r_ground);

	double r = compute_r(pos->h_rad, pos->h_ss_rad);

	double G = compute_G(H, r);

	double G_B = compute_G_B(G, pos->h_rad, pos->h_ss_rad);

	double G_D = compute_G_D(G, pos->h_rad, pos->h_ss_rad);





	double cos_theta = compute_cos_theta(L_rad, beta_rad, Z_S_rad, pos->delta_rad, pos->h_rad);

	double R_B = compute_R_B(cos_theta, pos->cos_Phi);

	double M = compute_M(pos->m, a0, a1, a2, a3, a4);

	double theta_r = compute_theta_r(acos(cos_theta), n_refraction_index);

	double theta_e_D = compute_theta_e_D(beta_rad);

	double taualpha_B = compute_taualpha_B(K, thickness, theta_r, acos(cos_theta));

	double taualpha_D = compute_taualpha_D(K, thickness, theta_r, theta_e_D);

	double taualpha_n = compute_taualpha_n(K, thickness, n_refraction_index);

	double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n);

	double K_theta_D = compute_K_theta_D(taualpha_D, taualpha_n);

	double S_B = taualpha_n * M * G_B * R_B * K_theta_B;

	double S_D = taualpha_n * M * G_D * K_theta_D * ((1 - cos(beta_rad)) / 2);

	double S = S_B + S_D;





	debug_output->G_on = G_on;

	debug_output->G_oH = G_oH;

	debug_output->H_o_rad = H_o_rad;

	debug_output->H_o = H_o;

	debug_output->r_ground = r_ground;

	debug_output->H = H;

	debug_output->r = r;

	debug_output->G = G;

	debug_output->G_B = G_B;

	debug_output->G_D = G_D;

	debug_output->cos_theta = cos_theta;

	debug_output->R_B = R_B;

	debug_output->M = M;

	debug_output->theta_r = theta_r;

	debug_output->theta_e_D = theta_e_D;

	debug_output->taualpha_B = taualpha_B;

	debug_output->taualpha_D = taualpha_D;

	debug_output->taualpha_n = taualpha_n;

	debug_output->K_theta_B = K_theta_B;

	debug_output->K_theta_D = K_theta_D;

	debug_output->S_B = S_B;

	debug_output->S_D = S_D;

	debug_output->S = S;



	return S;



}

