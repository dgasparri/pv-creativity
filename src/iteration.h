#include <vector>
#include <functional>
#include <thread>
#include "lib/sun_fp.h"


namespace iteration {
    pv_sun::position_in_sky* sun_position_matrix(double L_rad, int day_start, int day_end, int minutes_start, int minutes_in_step, int n_steps);
    geometry::triangle* panel_triangle_array();
    double S_thread();
}