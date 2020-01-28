#include "../config.h"
#include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
#include "../lib/sun_panel_fp.h"
#include "../lib/geometry_fp.h"
#include <algorithm>
#include <cmath>


namespace panel_irradiance {
    const double compute_S(
        const pv_sun::position_in_sky* pos,
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
        double a4
    );


}

