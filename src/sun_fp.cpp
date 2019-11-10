#include "src/sun_fp.h"


pure double cos_Phi(int N, int minutes, int L_rad)
{
    double delta_rad = compute_delta_rad(N);
    double h_rad = compute_h_rad(minutes);
    return compute_cos_Phi(L_rad, delta_rad, h_rad);
}

pure double Phi_rad(int N, int minutes, int L_rad) 
{
    return acos(cos_Phi_rad(N, minutes, L_rad));
}

pure double sin_alpha(int N, int minutes, int L_rad)
{
    double delta_rad = compute_delta_rad(N);
    double h_rad = compute_h_rad(minutes);
    return compute_cos_Phi(L_rad, delta_rad, h_rad);
}

pure double alpha_rad(int N, int minutes, int L_rad)
{
    return asin(sin_alpha(N, minutes, L_rad));
}

pure double m(int N, int minutes, int L_rad) {
	return 1 / cos_Phi(N, minutes, L_rad);
}



//Eq. 1n
pure double compute_delta_rad(int N) {
	double parenthesis = (284 + N) * 360 / 365;
	return 23.45 * sin(parenthesis * M_PI / 180) * M_PI / 180;
}

//Eq. 2n
//TODO che significa il + e -???
pure double compute_h_rad(int minutes) {
	return 0.25 * minutes * M_PI / 180;
}

// Eq. 3 n
// Output cos(Phi) Zenith Angle
pure double compute_cos_Phi(double L_rad, double delta_rad, double h_rad) {
	return sin(L_rad) * sin(delta_rad) + cos(L_rad) * cos(delta_rad) * cos(h_rad);
}


