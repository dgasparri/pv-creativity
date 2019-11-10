#include "src/panel_geometry_fp.h"
#include <functional>
#include <vector>
#include <iostream>

struct vertex {
    const double x;
    const double y;
    const double z;
    vertex(double x, double y, double z):
         x(x), y(y), z(z) {}

    vertex operator-(const vertex& other) const {
        std::cout<<"y "<<y <<" y other "<<other.y<<std::endl;
        return vertex(x-other.x, y-other.y, z-other.z);
    }
};

struct rectangle {
    vertex ne;
    vertex nw;
    vertex sw;
    vertex se;
};

//Get the tilt from a panel
pure double beta_rad(vertex a, vertex b, vertex c, vertex d) 
{

}

pure double Z_s_rad(vertex a, vertex b, vertex c, vertex d)
{

}

pure rectangle vertex_to_plane(vertex a, vertex b, vertex c, vertex d)
{


}

//Ritorna il vettore normale al piano
pure vertex normal(vertex a, vertex b, vertex c, vertex d)
{

}

//ulp: the desired precision in ULPs (units in the last place)
pure bool is_valid_parallelogram(vertex a, vertex b, vertex c, vertex d, int ulp = 3) 
{

    std::function is_equal = [](double x, double y, int ulp)-> bool{    
        // the machine epsilon has to be scaled to the magnitude of the values used
        // and multiplied by the desired precision in ULPs (units in the last place)
        return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp
                // unless the result is subnormal
                || std::fabs(x-y) < std::numeric_limits<double>::min();
    };

    vertex a(0,0,0);
    vertex b(0,1,0);
    vertex c(1,1,0);
    vertex d(1,0,0);


    vertex ab = b - a;
    vertex bc = c - b;
    vertex cd = d - c;
    vertex da = a - d;

    // ab.x = alpha * cd.x => ab.x/cd.x=alpha and cd.x/ab.x=1/alpha
    // 1 - 1 = 0 if ab and cd are parallel
    double ab_cd_iszero = ab.x * cd.y / (ab.y * cd.x) - ab.x * cd.z / (ab.z * cd.x);
    double bc_da_iszero = bc.x * da.y / (bc.y * da.x) - bc.x * da.z / (bc.z * da.x);
    


    return is_equal(ab_cd_iszero, 0.0, 3)
            && is_equal(bc_da_iszero, 0.0, 3);
}
