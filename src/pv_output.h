#pragma once



void compute_absorbed_radiation_S(
	double L = 35, //Latitute degrees
	double beta = 30, //tilt/slope paneldegrees
	double delta = 23.09, //Degrees sole
	double G_B = 715 // W/m^2
);


double compute_cos_theta(double L, double beta, double delta, double h);

//Eq. 9
//Glass refraction index = 1.526
double compute_theta_r(double theta, double n_refraction_index = 1.526);

//Eq. 10
double compute_taualpha_B(double K, double thickness, double theta_r, double theta);

// Eq. 14
// Output cos(Phi)
double compute_cos_zenith_angle(double L, double delta, double h);

// Eq. 15
double compute_m(double cos_zenith_angle);

// Eq. 16
double compute_M(double m, double a0, double a1, double a2, double a3, double a4);

//Eq. 17
double compute_R_B(double cos_theta, double cos_zenith_angle);

//Eq. 13
double compute_K_theta_B(double taualpha_B, double taualpha_N);

// Eq. 12
double compute_taualpha_n(double K, double thickness, double n_refraction_index);

//Eq. 11
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B);


