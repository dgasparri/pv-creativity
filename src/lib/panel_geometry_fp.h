#pragma once
#define pure
#include <functional>
#include <cmath>

pure bool are_double_equal(double x, double y, int ulp);

namespace p_geometry {

    struct vertex {
        const double x;
        const double y;
        const double z;
        vertex(double x, double y, double z);

        vertex operator-(const vertex& other) const;
    };

    struct plane {
        //Eq. a_x * x + a_y * y + a_z * z = d
        const double a_x;
        const double a_y;
        const double a_z;
        const double d;
        plane(double a_x, double a_y, double a_z, double d);
    };

    struct triangle {
        const double beta_rad;
        const double Z_S_rad;
        const double area;
        triangle(const vertex a, const vertex b, const vertex c);
    };

    // pure double beta_rad(vertex a, vertex b, vertex c, vertex d);

    pure plane plane_from_vertices(const vertex a, const vertex b, const vertex d);
    pure vertex plane_normal(const plane pl);

    pure double beta_rad(const plane pl);
    pure double Z_S_rad(const plane pl);
    pure double vector_norm(const vertex pl_normal);

}


