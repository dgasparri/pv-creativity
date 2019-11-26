#include "sun_fp.h"


pure pv_sun::position_in_sky pv_sun::sun(
	const int N, // giorno dell'anno
	const int minutes, //minuti
	const double L_rad // = 35, //Latitute degrees
) {
    
    //    double alpha_rad;  //Solar altitude
    //    double z_rad; //Solar Azimuth
    //    double h_rad;
    //    int valid;
    pv_sun::position_in_sky pos(
        pv_sun::alpha_rad(N, minutes, L_rad),
        60.0, //must implement Solar Azimuth
        pv_sun::compute_h_rad(minutes),
        pv_sun::compute_delta_rad(N),
        pv_sun::cos_Phi(N, minutes, L_rad),
        pv_sun::compute_m(N, minutes, L_rad),
        1
    );
    return pos;
}



pure double pv_sun::cos_Phi(const int N, const int minutes, const double L_rad)
{
    double delta_rad = compute_delta_rad(N);
    double h_rad = compute_h_rad(minutes);
    return compute_cos_Phi(L_rad, delta_rad, h_rad);
}

pure double pv_sun::Phi_rad(const int N, const int minutes, const double L_rad) 
{
    return acos(cos_Phi(N, minutes, L_rad));
}

pure double pv_sun::sin_alpha(const int N, const int minutes, double L_rad)
{
    double delta_rad = compute_delta_rad(N);
    double h_rad = compute_h_rad(minutes);
    return compute_cos_Phi(L_rad, delta_rad, h_rad);
}

pure double pv_sun::alpha_rad(const int N, const int minutes, const double L_rad)
{
    return asin(sin_alpha(N, minutes, L_rad));
}

pure double pv_sun::compute_m(const int N, const int minutes, const double L_rad) {
	return 1 / cos_Phi(N, minutes, L_rad);
}



//Eq. 1n
//Ok
pure double pv_sun::compute_delta_rad(const int N) {
	double parenthesis = (284 + N) * 360 / 365;
	return 23.45 * sin(parenthesis * M_PI / 180) * M_PI / 180;
}

//Eq. 2n
//TODO che significa il + e -???
//Ok
pure double pv_sun::compute_h_rad(const int minutes) {
	return 0.25 * minutes * M_PI / 180;
}

// Eq. 3 n
// Output cos(Phi) Zenith Angle
//Ok
pure double pv_sun::compute_cos_Phi(const double L_rad, const double delta_rad, const double h_rad) {
	return sin(L_rad) * sin(delta_rad) + cos(L_rad) * cos(delta_rad) * cos(h_rad);
}


