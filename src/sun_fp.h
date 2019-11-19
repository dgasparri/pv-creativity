#pragma once
#define pure
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

/*
-------- Related to the sun and earth -------

Input:
 * N: day of year
 * minutes: from noon, negatives are morning, positives are afternoon
 * L_rad: latitude in radians

Output:
 * Phi (Zenith)
 * alpha (Altitude)
 * z (not yet)

*/

// ------ INTERFACES -----
pure double cos_Phi(int N, int minutes, int L_rad);
pure double Phi_rad(int N, int minutes, int L_rad);
pure double sin_alpha(int N, int minutes, int L_rad);
pure double alpha_rad(int N, int minutes, int L_rad);
pure double m(int N, int minutes, int L_rad);


// ----- INTERNAL ----
pure double compute_delta_rad(int N);
pure double compute_h_rad(int minutes);
pure double compute_cos_Phi(double L_rad, double delta_rad, double h_rad);


