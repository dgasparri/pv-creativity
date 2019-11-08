#include <windows.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#define PI 3.14159265


/* Da pressione di bottone
L: 35
beta: 30
Z_S: 0
L_T: 0.002
Refraction Index (n): 1.526
K: 4
Giorni (N): 165
Minuti (minutes): 0
G_B: 715
S: 641.003

*/


struct sun_position_in_sky {
	double alpha_rad;  //Solar altitude
	double z_rad; //Solar Azimuth
	double h;
	int valid;
};

void compute_absorbed_radiation_S(
	int N, // giorno dell'anno
	int minutes,
	double beta,
	double L
);



double compute_delta(int N);
double compute_h_rad(int minutes);
double compute_cos_Phi(double L_rad, double delta, double h);
double compute_cos_theta(double L_rad, double beta_rad, double Z_S_rad, double delta, double h);
double compute_theta_r(double theta, double n_refraction_index = 1.526);
double compute_taualpha_B(double K, double thickness, double theta_r, double theta);
double compute_cos_zenith_angle(double L, double delta, double h);
double compute_m(double cos_zenith_angle);
double compute_M(double m, double a0, double a1, double a2, double a3, double a4);
double compute_R_B(double cos_theta, double cos_zenith_angle);
double compute_K_theta_B(double taualpha_B, double taualpha_N);
double compute_taualpha_n(double K, double thickness, double n_refraction_index);
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B);
double compute_S925(double M, double G_B, double R_B, double tau_alpha_D);

double compute_sin_z(double delta_rad, double h_rad, double alpha_rad);














void compute_absorbed_radiation_S(
	int N, // giorno dell'anno
	int minutes, //minuti
	double beta,
	double L
) {
    double Z_S = 0;
	double G_B = 715; // W/m^2
	


	double K = 4; // m^-1
	double L_T = 0.002; // m la chiama L, thickness
	double n_refraction_index = 1.526;

	//Monocristallino Tabella pg. 514
	double alpha_0 = 0.935823;
	double alpha_1 = 0.054289;
	double alpha_2 = -0.008677;
	double alpha_3 = 0.000527;
	double alpha_4 = -0.000011;


	double delta = compute_delta(N); //Eq. 1n
	double h_rad = compute_h_rad(minutes); //Eq. 2n



	double L_rad = L * PI / 180;
	double delta_rad = delta * PI /180;
	double cos_Phi = compute_cos_Phi(L_rad, delta_rad, h_rad); //Eq. 3n
	double sin_alpha = cos_Phi;
	double alpha_rad = asin(sin_alpha);
	double sin_z = compute_sin_z(delta_rad, h_rad, alpha_rad);

	sun_position_in_sky sp;
	sp.z_rad = asin(sin_z);
	sp.alpha_rad = alpha_rad;
	if (cos(h_rad)> (tan(delta_rad)/tan(L))) {
		sp.valid = 1;
	} else {
		sp.valid = 0;
	}


	double beta_rad = beta * PI / 180;
	double Z_S_rad = Z_S * PI / 180;

	double cos_theta = compute_cos_theta(L_rad, beta_rad, 
		Z_S_rad, delta_rad, h_rad); //Eq. 4
	double theta_rad = acos(cos_theta);

	double R_B = compute_R_B(cos_theta, cos_Phi); //Eq. 5n
	double m = compute_m(cos_Phi); //Eq. 6n

	double M = compute_M(m, alpha_0, alpha_1, 
		alpha_2, alpha_3, alpha_4); //Eq. 7n

	double theta_r = compute_theta_r(theta_rad, n_refraction_index); //Eq. 8n

	double taualpha_B = compute_taualpha_B(K, L_T, 
		theta_r, theta_rad); //Eq. 9n

	double taualpha_n = compute_taualpha_n(K, L_T, 
		n_refraction_index); //Eq. 10n

	double K_theta_B = compute_K_theta_B(taualpha_B, taualpha_n); //Eq. 11n
	double S = compute_S(taualpha_n, M, G_B, R_B, K_theta_B); //Eq. 12n
	double S925 = compute_S925(M, G_B, R_B, taualpha_B);
	if(N % 60 ==0) {
	std::cout<<N << " taualpha_n: " << taualpha_n << std::endl
			<< " cos_Phi: " << cos_Phi << std::endl
			<< " M: " << M << std::endl 
			<< " G_B: " << G_B << std::endl
			<< " R_B: " << R_B << std::endl
			<< " K_theta_B: " << K_theta_B << std::endl
			<< " S: " << S << std::endl
			<< " S925: " << S925 << std::endl
			;
	}


}

double compute_sin_z(double delta_rad, double h_rad, double alpha_rad) {
	return cos(delta_rad) * sin(h_rad) / cos(alpha_rad);
}


double compute_par(int N) {
	double parenthesis = (284 - N) / 365;
	return parenthesis;
}
//Eq. 1n
double compute_delta(int N) {
	double parenthesis = (284 + N) * 360 / 365;
	return 23.45 * sin(parenthesis * PI / 180);
}

//Eq. 2n
//TODO che significa il + e -???
//TODO
double compute_h_rad(int minutes) {
	return 0.25 * minutes * PI / 180;
}

// Eq. 3 n
// Output cos(Phi) Zenith Angle
//TODO
double compute_cos_Phi(double L_rad, double delta_rad, double h) {
	return (sin(L_rad) * sin(delta_rad)) + (cos(L_rad) * cos(delta_rad) * cos(h));
}

//Eq. 3.bis n
//Output alpha (complementare dell'angolo di Zenith)
//DA FARE


//Eq. 4n
//TODO
double compute_cos_theta(double L_rad, double beta_rad, double Z_S_rad, double delta_rad, double h) {
	return sin(L_rad) * sin(delta_rad) * cos(beta_rad)
		- cos(L_rad) * sin(delta_rad) * sin(beta_rad) * cos(Z_S_rad)
		+ cos(L_rad) * cos(delta_rad) * cos(h) * cos(beta_rad)
		+ sin(L_rad) * cos(delta_rad) * cos(h) * sin(beta_rad) * cos(Z_S_rad)
		+ cos(delta_rad) * sin(h) * sin(beta_rad) * sin(Z_S_rad);
}


//Eq. 5n
double compute_R_B(double cos_theta, double cos_Phi) {
	return cos_theta / cos_Phi;
}

//Eq. 6n
double compute_m(double cos_Phi) {
	return (1 / cos_Phi);
}

//Eq. 7n
double compute_M(double m, double a0, double a1, double a2, double a3, double a4) {
	return a0
		+ a1 * m
		+ a2 * std::pow(m, 2) 
		+ a3 * std::pow(m, 3) 
		+ a4 * std::pow(m, 4);
}

//Eq. 8n
//Glass refraction index = 1.526
double compute_theta_r(double theta, double n_refraction_index) {
	return asin(sin(theta) / n_refraction_index);
}

//Eq. 9n
double compute_taualpha_B(double K, double thickness, double theta_r, double theta) {
	double theta_diff = theta_r - theta;
	double theta_sum = theta_r + theta;
	double inner_square_brakes = 
		std::pow(sin(theta_diff), 2) / std::pow(sin(theta_sum), 2)
		+ std::pow(tan(theta_diff), 2) / std::pow(tan(theta_sum) , 2);
	double curly_brakets = 1 - inner_square_brakes / 2;
	double exponent = -(K * thickness / cos(theta_r));
	return exp(exponent) * curly_brakets;
}

// Eq. 10n
double compute_taualpha_n(double K, double thickness, double n_refraction_index) {
	double fraction_n = std::pow((n_refraction_index - 1) / (n_refraction_index + 1), 2);
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

double compute_S925(double M, double G_B, double R_B, double tau_alpha_D) {
	return M * G_B * R_B * tau_alpha_D;
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