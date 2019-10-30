#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <FL/Fl_Text_Buffer.H>
#include "pv_output.h"

#define PI 3.14159265

extern Fl_Text_Buffer* resultsBuffer;

double compute_absorbed_radiation_S(
	double L, // = 35, //Latitute degrees
	double beta, // = 30, //tilt/slope paneldegrees
	double delta, // = 23.09, //Degrees sole
	double G_B, // = 715 // W/m^2
	int printToBuffer
) {
	/*
	double L = 35; //Latitute degrees
	double beta = 30; //tilt/slope paneldegrees
	double delta = 23.09; //Degrees sole
	double G_B = 715; // W/m^2
	*/



	double n_refraction_index = 1.526;
	double K = 4; // m^-1
	double thickness = 0.002; // m la chiama L


	double h = 0; // Non so cosa sia

	double L_rad = L * PI / 180;
	double beta_rad = beta * PI / 180;
	double delta_rad = delta * PI / 180;


	//Monocristallino Tabella pg. 514
	double alpha_0 = 0.935823;
	double alpha_1 = 0.054289;
	double alpha_2 = -0.008677;
	double alpha_3 = 0.000527;
	double alpha_4 = -0.000011;

	//ATTENZIONE QUESTA L non è 0.002;
	double cos_theta = compute_cos_theta(L_rad, beta_rad, delta_rad, h);
	double theta = acos(cos_theta);
	double theta_r = compute_theta_r(theta, n_refraction_index);

	double taualpha_B = compute_taualpha_B(K, thickness, theta_r, theta);
	double taualpha_n = compute_taualpha_n(K, thickness, n_refraction_index);
	double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n);


	double cos_zenith_angle = compute_cos_zenith_angle(L_rad, delta_rad, h);
	double m = compute_m(cos_zenith_angle);
	double M = compute_M(m, alpha_0, alpha_1, alpha_2, alpha_3, alpha_4);

	double R_B = compute_R_B(cos_theta, cos_zenith_angle);

	double S = compute_S(taualpha_n, M, G_B, R_B, K_theta_B);

	std::cout << "TauAlpha_n: " << taualpha_n << std::endl
		<< "M: " << M << std::endl
		<< "G_B: " << G_B << std::endl
		<< "R_B: " << R_B << std::endl
		<< "K_theta_B: " << K_theta_B << std::endl
		<< "S: " << S << std::endl;

	char strbuffer[500];
	sprintf_s(strbuffer, 500, "Buffer: TauAlpha_n: %f\nM: %f\nG_B: %f\nR_B: %f\nK_theta_B: %f\nS: %f  [W/m^2]\n", taualpha_n, M, G_B, R_B, K_theta_B, S);
	if (printToBuffer) {
		resultsBuffer->text(strbuffer);
	}

	return S;

}



double compute_cos_theta(double L, double beta, double delta, double h) {
	return sin(L - beta) * sin(delta) + cos(L - beta) * cos(delta) * cos(h);
}




//Eq. 9
//Glass refraction index = 1.526
double compute_theta_r(double theta, double n_refraction_index) {
	return asin(sin(theta) / n_refraction_index);
}

//Eq. 10
double compute_taualpha_B(double K, double thickness, double theta_r, double theta) {
	double theta_diff = theta_r - theta;
	double theta_sum = theta_r + theta;
	double inner_square_brakes = pow(sin(theta_diff) / sin(theta_sum), 2)
		+ pow(tan(theta_diff) / tan(theta_sum), 2);
	double curly_brakets = 1 - inner_square_brakes / 2;
	double exponent = -(K * thickness / cos(theta_r));
	return exp(exponent) * curly_brakets;
}

// Eq. 14
// Output cos(Phi)
double compute_cos_zenith_angle(double L, double delta, double h) {
	return sin(L) * sin(delta) + cos(L) * cos(delta) * cos(h);
}

// Eq. 15
double compute_m(double cos_zenith_angle) {
	return 1 / cos_zenith_angle;
}

// Eq. 16
double compute_M(double m, double a0, double a1, double a2, double a3, double a4) {
	return a0
		+ a1 * m
		+ a2 * pow(m, 2)
		+ a3 * pow(m, 3)
		+ a4 * pow(m, 4);
}

//Eq. 17
double compute_R_B(double cos_theta, double cos_zenith_angle) {
	return cos_theta / cos_zenith_angle;
}

//Eq. 13
double compute_K_theta_B(double taualpha_B, double taualpha_N) {
	return taualpha_B / taualpha_N;
}

// Eq. 12
double compute_taualpha_n(double K, double thickness, double n_refraction_index) {
	double fraction_n = pow((n_refraction_index - 1) / (n_refraction_index + 1), 2);
	return exp(-1 * K * thickness) * (1 - fraction_n);
}

//Eq. 11
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B) {
	return taualpha_n * M * G_B * R_B * K_theta_B;
}

// Eq. 1
double compute_I(double I_ph, double I_0, double q, double V_d, double a, double k, double T) {
	return I_ph - I_0 * (exp(((q * V_d) / (a * k * T)) - 1));
}

// Eq. 2
double compute_I2(double I, double R_s, double V ,double I_ph, double I_0, double R_p, double V_T, double a) {
	double var1 = (exp((V + I * R_s) / (a * V_T))) - 1;
	double var2 = ((V + I * R_s) / R_p);
	return I_ph - I_0 * var1 - var2;
}

// Eq. 3
double compute_V_T(double N_S, double K, double T, double q) {
	return (N_S * K * T) / q;
}

//Eq. 4
double compute_I_ph(double I_phSTC, double K_j, double delta_T, double G, double G_STC) {
	return (I_phSTC + K_j * delta_T) * G / G_STC;
}

// Eq. 5
double compute_I_0(double V_ocSTC, double I_phSTC, double K_j, double delta_T, double K_V, double a, double V_T) {
	double var1 = exp((V_ocSTC + K_V * delta_T) / (a * V_T));
	return (I_phSTC + K_j * delta_T) / (var1 - 1);
}
 
// Eq. 6
double compute_I3(double I_01, double R_s, double V, double I_ph, double I, double I_02, double R_p, double V_T1, double a_1, double V_T2, double a_2) {
	double var1 = (exp((V + I * R_s) / (a_1 * V_T1))) - 1;
	double var2 = (exp((V + I * R_s) / (a_2 * V_T2))) - 1;
	double var3 = ((V + I * R_s) / R_p);
	return I_ph + I_01 * var1 - I_02 * var2 - var3;
}

//Eq. 7
//double compute_I01_I02()