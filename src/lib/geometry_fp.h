#pragma once
#include "../global.h"
#include <functional>
#include <cmath>
#include <iostream>

pure bool are_double_equal(double x, double y, int ulp);

namespace geometry {

    struct vertex {
        const double x;
        const double y;
        const double z;
        vertex(double x, double y, double z);

        vertex operator-(const vertex& other) const;
        bool operator==(const vertex& other) const;
        friend std::ostream& operator<<(std::ostream& os, const vertex& v);
    };

    struct plane {
        //Eq. a_x * x + a_y * y + a_z * z = d
        const double a_x;
        const double a_y;
        const double a_z;
        const double d;
        plane(double a_x, double a_y, double a_z, double d);
        friend std::ostream& operator<<(std::ostream& os, const plane& pl);
    };

    typedef double Z_S_rad;
    typedef plane plane_xparallel;
    typedef vertex plane_normal_vector;
    typedef double m_squared;
    typedef double beta_rad;

    struct triangle {
        const beta_rad mbeta_rad;
        const Z_S_rad mZ_S_rad;
        const m_squared marea;
        const plane_normal_vector mplane_normal;
        triangle(const vertex a, const vertex b, const vertex c);
    };

    pure plane fplane(const vertex a, const vertex b, const vertex d);
    pure plane_normal_vector fnormal(const plane pl);
    pure Z_S_rad fZ_S_rad(const plane pl);
    pure beta_rad fbeta_rad(const vertex a, const vertex b, const vertex d, const Z_S_rad Z_S);
    pure m_squared farea(const vertex a, const vertex b, const vertex d);

    pure vertex rotate_vertex_zaxis(const vertex v, const double angle_rad);
    pure plane rotate_plane_zaxis(const vertex a, const vertex b, const vertex d, const double angle_rad);
    pure plane_xparallel rotate_plane_to_xparallel(const vertex a, const vertex b, const vertex d, const Z_S_rad mZ_S_rad);


    pure double fnorm(const vertex pl);

}


