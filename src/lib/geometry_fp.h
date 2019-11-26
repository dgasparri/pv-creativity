#pragma once
#define pure
#define _USE_MATH_DEFINES
#include <functional>
#include <cmath>

pure bool are_double_equal(double x, double y, int ulp);

namespace geometry {

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

    typedef double Z_S_rad;

    struct triangle {
        const double beta_rad;
        const Z_S_rad Z_S_rad;
        const double area;
        const vertex plane_normal;
        triangle(const vertex a, const vertex b, const vertex c);
    };

    typedef plane plane_xparallel;
    // pure double beta_rad(vertex a, vertex b, vertex c, vertex d);

    pure plane plane_from_vertices(const vertex a, const vertex b, const vertex d);
    pure vertex normal_vector_from_plane(const plane pl);
    pure Z_S_rad Z_S_rad_from_plane(const plane pl);

    pure vertex rotate_zaxis(const vertex v, const double angle);
    pure plane plane_rotate_zaxis(const vertex a, const vertex b, const vertex d, const double angle);
    pure plane_xparallel rotate_plane_to_xparallel(const vertex a, const vertex b, const vertex d, const Z_S_rad Z_S_rad);
    pure double beta_rad_from_plane(const plane_xparallel pl_xparallel);

    
    pure double vector_norm(const vertex pl_normal);

}


