#pragma once
#define pure
#include <cmath>

// Eq. 1
pure double compute_I(double I_ph, double I_0, double q, double V_d, double a, double k, double T) {
	return I_ph - I_0 * (exp(((q * V_d) / (a * k * T)) - 1));
}

// Eq. 2
pure double compute_I2(double I, double R_s, double V ,double I_ph, double I_0, double R_p, double V_T, double a) {
	double var1 = (exp((V + I * R_s) / (a * V_T))) - 1;
	double var2 = ((V + I * R_s) / R_p);
	return I_ph - I_0 * var1 - var2;
}

// Eq. 3
pure double compute_V_T(double N_S, double K, double T, double q) {
	return (N_S * K * T) / q;
}

//Eq. 4
pure double compute_I_ph(double I_phSTC, double K_j, double delta_T, double G, double G_STC) {
	return (I_phSTC + K_j * delta_T) * G / G_STC;
}

// Eq. 5
pure double compute_I_0(double V_ocSTC, double I_phSTC, double K_j, double delta_T, double K_V, double a, double V_T) {
	double var1 = exp((V_ocSTC + K_V * delta_T) / (a * V_T));
	return (I_phSTC + K_j * delta_T) / (var1 - 1);
}
 
// Eq. 6
pure double compute_I3(double I_01, double R_s, double V, double I_ph, double I, double I_02, double R_p, double V_T1, double a_1, double V_T2, double a_2) {
	double var1 = (exp((V + I * R_s) / (a_1 * V_T1))) - 1;
	double var2 = (exp((V + I * R_s) / (a_2 * V_T2))) - 1;
	double var3 = ((V + I * R_s) / R_p);
	return I_ph + I_01 * var1 - I_02 * var2 - var3;
}

//Eq. 7
//double compute_I01_I02()