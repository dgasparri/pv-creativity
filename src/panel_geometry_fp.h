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

    // pure double beta_rad(vertex a, vertex b, vertex c, vertex d);
    pure bool is_valid_parallelogram(vertex a, vertex b, vertex c, vertex d, int ulp = 3);
    pure plane plane_from_vertices(vertex a, vertex b, vertex d);
    pure bool is_vertex_on_plane(plane pl, vertex c, int ulp = 3);
    pure vertex plane_normal(plane pl);
    pure vertex diagonal_intersection(vertex a, vertex b, vertex c, vertex d, int ulp = 3);
    pure double beta_rad(plane pl);
    pure double Z_S_rad(plane pl); 

}


