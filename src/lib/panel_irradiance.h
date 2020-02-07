#include "../global.h"
#include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
// #include "../lib/sun_panel_fp.h"
#include "../lib/geometry_fp.h"
#include <algorithm>
#include <cmath>


namespace panel_irradiance {

    struct s_debug {
        double G_on; 
        double G_oH;        
        double H_o_rad;
        double H_o;
        double r_ground;
        double H;
        double r;
        double G;
        double G_B;
        double G_D;
        double cos_theta;
        double R_B;
        double M;
        double theta_r;
        double theta_e_D;
        double taualpha_B;
        double taualpha_D;
        double taualpha_n;
        double K_theta_B;
        double K_theta_D;
        double S_B;
        double S_D;
        double S;
    };

    const double compute_S(
        const pv_sun::position_in_sky* pos,
        int N,
        double L_rad,
        double beta_rad,
        double Z_S_rad,
        double n_refraction_index, 
        double thickness, 
        double K,
        double a0,
        double a1,
        double a2,
        double a3,
        double a4,
        s_debug *debug_output = NULL
    );

}

