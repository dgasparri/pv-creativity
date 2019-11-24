#include "irradiance_fp.h"




//Eq. 4n
pure double compute_cos_theta(double L_rad, double beta_rad, double Z_S_rad, double delta_rad, double h_rad) {
	return sin(L_rad) * sin(delta_rad) * cos(beta_rad)
		- cos(L_rad) * sin(delta_rad) * sin(beta_rad) * cos(Z_S_rad)
		+ cos(L_rad) * cos(delta_rad) * cos(h_rad) * cos(beta_rad)
		+ sin(L_rad) * cos(delta_rad) * cos(h_rad) * sin(beta_rad) * cos(Z_S_rad)
		+ cos(delta_rad) * sin(h_rad) * sin(beta_rad) * sin(Z_S_rad);
}

//Eq. 5n
double compute_R_B(double cos_theta, double cos_Phi) {
	return cos_theta / cos_Phi;
}


//Eq. 7n
double compute_M(double m, double a0, double a1, double a2, double a3, double a4) {
	return a0
		+ a1 * m
		+ a2 * pow(m, 2)
		+ a3 * pow(m, 3)
		+ a4 * pow(m, 4);
}

//Eq. 8n
//Glass refraction index = 1.526
double compute_theta_r(double theta_rad, double n_refraction_index) {
	return asin(sin(theta_rad) / n_refraction_index);
}

//Eq. 9n
double compute_taualpha_B(double K, double thickness, double theta_r, double theta) {
	double theta_diff = theta_r - theta;
	double theta_sum = theta_r + theta;
	double inner_square_brakes = pow(sin(theta_diff) / sin(theta_sum), 2)
		+ pow(tan(theta_diff) / tan(theta_sum), 2);
	double curly_brakets = 1 - inner_square_brakes / 2;
	double exponent = -(K * thickness / cos(theta_r));
	return exp(exponent) * curly_brakets;
}

// Eq. 10n
double compute_taualpha_n(double K, double thickness, double n_refraction_index) {
	double fraction_n = pow((n_refraction_index - 1) / (n_refraction_index + 1), 2);
	return exp(-1 * K * thickness) * (1 - fraction_n);
}

//Eq. 11n
double compute_K_theta_B(double taualpha_B, double taualpha_N) {
	return taualpha_B / taualpha_N;
}

//Eq. 12n
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B) {
	return taualpha_n * M * G_B * R_B * K_theta_B;
}

