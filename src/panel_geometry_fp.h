#pragma once
#define pure
#include <functional>
#include <cmath>

namespace p_geometry {

    struct vertex {
        const double x;
        const double y;
        const double z;
        vertex(double x, double y, double z);

        vertex operator-(const vertex& other) const;
    };

    // pure double beta_rad(vertex a, vertex b, vertex c, vertex d);
    pure bool is_valid_parallelogram(vertex a, vertex b, vertex c, vertex d, int ulp = 3);
}


