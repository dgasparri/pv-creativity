#pragma once
#define pure

#include "../config.h"


#include <cmath>


pure double compute_cos_theta(double L_rad, double beta_rad, double Z_S_rad, double delta_rad, double h_rad);
pure double compute_R_B(double cos_theta, double cos_Phi);
pure double compute_M(double m, double a0, double a1, double a2, double a3, double a4);
pure double compute_theta_r(double theta_rad, double n_refraction_index);
pure double compute_theta_e_D(double beta_rad);
pure double compute_taualpha_B(double K, double thickness, double theta_r, double theta);
pure double compute_taualpha_D(double K, double thickness, double theta_r, double theta_e_D);
pure double compute_taualpha_n(double K, double thickness, double n_refraction_index);
pure double compute_K_theta_B(double taualpha_B, double taualpha_N);
pure double compute_K_theta_D(double taualpha_D, double taualpha_N);

namespace irradiance {
    pure double compute_G_on(const int N, const double G_SC=G_SC_CONSTANT);
    pure double compute_G_oH(const double G_on, const double cos_Phi);
    pure double compute_H_o_rad(const double L_rad, const double delta_rad, const double h_ss_rad, const double G_on);
    pure double compute_H_o(const double H_o_rad);
    pure double compute_r_ground(const int N);
    pure double compute_H(const double H_o, const double r_ground);
    pure double compute_r(const double h_rad, const double h_ss_rad);
    pure double compute_G(const double H, const double r);
    //pure double compute_G_o(const double G_oH, const double r);
    pure double compute_G_B(const double G_o, const double h_rad, const double h_ss_rad);
    pure double compute_G_D(const double G_o, const double h_rad, const double h_ss_rad);
}












//Eq. 12n
//double compute_S(double taualpha_n, double M, double G_B, double R_B, double K_theta_B);

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
