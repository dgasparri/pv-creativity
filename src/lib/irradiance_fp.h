#pragma once
#define pure

#include <math.h>



//Eq. 4n
pure double compute_cos_theta(double L_rad, double beta_rad, double Z_S_rad, double delta_rad, double h_rad);

//Eq. 5n
double compute_R_B(double cos_theta, double cos_Phi);


//Eq. 7n
double compute_M(double m, double a0, double a1, double a2, double a3, double a4);

//Eq. 8n
//Glass refraction index = 1.526
double compute_theta_r(double theta_rad, double n_refraction_index);

//Eq. 9n
double compute_taualpha_B(double K, double thickness, double theta_r, double theta);

// Eq. 10n
double compute_taualpha_n(double K, double thickness, double n_refraction_index);

//Eq. 11n
double compute_K_theta_B(double taualpha_B, double taualpha_N);

//Eq. 12n
double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B);

// Eq. 1
double compute_I(double I_ph, double I_0, double q, double V_d, double a, double k, double T);

// Eq. 2
double compute_I2(double I, double R_s, double V ,double I_ph, double I_0, double R_p, double V_T, double a);

// Eq. 3
double compute_V_T(double N_S, double K, double T, double q);

//Eq. 4
double compute_I_ph(double I_phSTC, double K_j, double delta_T, double G, double G_STC);

// Eq. 5
double compute_I_0(double V_ocSTC, double I_phSTC, double K_j, double delta_T, double K_V, double a, double V_T);
 
// Eq. 6
double compute_I3(double I_01, double R_s, double V, double I_ph, double I, double I_02, double R_p, double V_T1, double a_1, double V_T2, double a_2);
