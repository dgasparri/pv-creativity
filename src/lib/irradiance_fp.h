#pragma once
#define pure

#include "../global.h"


#include <cmath>



namespace irradiance {
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





