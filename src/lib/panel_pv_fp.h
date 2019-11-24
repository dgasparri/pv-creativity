#pragma once
#define pure
#include <cmath>

// Eq. 1
pure double compute_I(double I_ph, double I_0, double q, double V_d, double a, double k, double T);

// Eq. 2
pure double compute_I2(double I, double R_s, double V ,double I_ph, double I_0, double R_p, double V_T, double a);

// Eq. 3
pure double compute_V_T(double N_S, double K, double T, double q);

//Eq. 4
pure double compute_I_ph(double I_phSTC, double K_j, double delta_T, double G, double G_STC);

// Eq. 5
pure double compute_I_0(double V_ocSTC, double I_phSTC, double K_j, double delta_T, double K_V, double a, double V_T);
 
// Eq. 6
pure double compute_I3(double I_01, double R_s, double V, double I_ph, double I, double I_02, double R_p, double V_T1, double a_1, double V_T2, double a_2);

//Eq. 7
//double compute_I01_I02()