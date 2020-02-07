#pragma once
#define pure

#include "../global.h"

#include <cmath>


namespace pv_sun {


    /*
    -------- Related to the sun and earth -------

    Input:
    * N: day of year
    * minutes: from noon, negatives are morning, positives are afternoon
    * L_rad: latitude in radians

    Output:
    * cos_Phi (Zenith)
    * alpha_rad (Altitude)
    * h_rad
    * h_ss_rad
    * delta_rad
    * cos_Phi
    * m
    * valid

    */


    struct position_in_sky {
        const double alpha_rad;  //Solar altitude
        const double z_rad; //Solar Azimuth
        const double h_rad;
        const double h_ss_rad;
        const double delta_rad;
        const double cos_Phi;
        const double m;
        const bool valid;
  
        position_in_sky(
            const double alpha_rad,
            const double z_rad,
            const double h_rad,
            const double h_ss_rad,
            const double delta_rad,
            const double cos_Phi,
            const double m,
            const int valid
        ) : 
            alpha_rad(alpha_rad),
            z_rad(z_rad),
            h_rad(h_rad),
            h_ss_rad(h_ss_rad),
            delta_rad(delta_rad),
            cos_Phi(cos_Phi),
            m(m),
            valid(valid) {};

    };

    pure position_in_sky* sun(const int N, const int minutes, const double L_rad);


    // ------ INTERFACES -----
    pure double cos_Phi(const int N, const int minutes, const double L_rad);
    pure double Phi_rad(const int N, const int minutes, const double L_rad);
    pure double sin_alpha(const int N, const int minutes, const double L_rad);
    pure double alpha_rad(const int N, const int minutes, const double L_rad);
    pure double compute_m(const int N, const int minutes, const double L_rad);
    

    // ----- INTERNAL ----
    pure double compute_delta_rad(const int N);
    pure double compute_h_rad(const int minutes);
    pure double compute_h_ss_rad(const double L_rad, const double delta_rad);
    pure double compute_cos_Phi(const double L_rad, const double delta_rad, const double h_rad);
    pure double compute_z_rad(const double delta_rad, const double h_rad, const double alpha_rad);



}
