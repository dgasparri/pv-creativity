#pragma once
#define pure
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include "sun_fp.h"
#include "irradiance_fp.h"
#include "panel_pv_fp.h"



pure double absorbed_radiation_S(
    const double L_rad,
    const pv_sun::position_in_sky pos,
    const double beta_rad,
    const double Z_S_rad
);