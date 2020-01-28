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



pure double compute_G_on(const int N, const double G_SC=G_SC_CONSTANT) {
	return G_SC*(1+0.033 * cos(2 * M_PI * N /365)); //substituted 360 with 2PI
}

pure double compute_G_oH(const double G_on, const double cos_Phi) {
	return G_on * cos_Phi;
}

pure double compute_H_o_rad(const double L_rad, const double delta_rad, const double h_ss_rad, const double G_on) {
	return 2 * G_on *(
		cos(L_rad)*cos(delta_rad)*sin(h_ss_rad)
		+ h_ss_rad * sin(L_rad) * sin(delta_rad)
	);
}

pure double compute_H_o(const double H_o_rad) {
	return H_o_rad * 24 * 60 *60 / (2 * M_PI);
}

pure double compute_r_ground(const int N) {
	if(N<= 31) return 0.61;
	if(N<= 59) return 0.64;
	if(N<= 90) return 0.67;
	if(N<=120) return 0.67;
	if(N<=151) return 0.67;
	if(N<=181) return 0.67;
	if(N<=212) return 0.67;
	if(N<=243) return 0.67;
	if(N<=273) return 0.64;
	if(N<=304) return 0.61;
	if(N<=334) return 0.55;
	return 0.55;
}
pure double compute_H(const double H_o, const double r_ground) {
	return H_o*r_ground;
}

pure double compute_r(const double h_rad, const double h_ss_rad) {
	const double alpha = 0.409+0.5016*sin(h_ss_rad - M_PI / 3); //60 gradi
	const double beta = 0.6609-0.4767*sin(h_ss_rad - M_PI / 3); //60 gradi
	return M_PI / 24 
		* ( alpha + beta * cos(h_rad))
		* (cos(h_rad)-cos(h_ss_rad))
		/ (sin(h_ss)-h_ss_rad*cos(h_ss_rad);) 
}
pure double compute_G(const double H, const double r) {
	return H*r;
}
pure double compute_G_B(const double G, const double h_rad, const double h_ss_rad) {
	return 0.6 * G +
		0.25 * (std:abs(h_ss_rad)-std:abs(h_rad)) * 2 / M_PI * G;
}
pure double compute_G_D(const double G, const double h_rad, const double h_ss_rad) {
	return 0.4 * G -
		0.25 * (std:abs(h_ss_rad)-std:abs(h_rad)) * 2 / M_PI * G;
}



//Eq. 12n
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B) {
	return taualpha_n * M * G_B * R_B * K_theta_B;
}

