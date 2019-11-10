#include "panel_geometry_fp.h"


/*
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
*/


namespace p_geometry {

    
    vertex::vertex(double x, double y, double z):
            x(x), y(y), z(z) {}

    vertex vertex::operator-(const vertex& other) const {
        return vertex(x-other.x, y-other.y, z-other.z);
    }
    


    //ulp: the desired precision in ULPs (units in the last place)
    //corollary: length(ab) = length(cd) and length(bc)=length(da)
    pure bool is_valid_parallelogram(vertex a, vertex b, vertex c, vertex d, int ulp) 
    {

        vertex ab = b - a;
        vertex bc = c - b;
        vertex cd = d - c;
        vertex da = a - d;

        // v1.x = alpha * v2.x
        // -999 if zero vector
        std::function<double(vertex, vertex)> get_alpha = [](vertex v1, vertex v2) -> double {
            if(v2.x) return v1.x / v2.x;
            if(v2.y) return v1.y / v2.y;
            if(v2.z) return v1.z / v2.z;
            return -999.0;
        };

        std::function<bool(double, double, int)> are_double_equal = [](double x, double y, int ulp)-> bool{    
            // the machine epsilon has to be scaled to the magnitude of the values used
            // and multiplied by the desired precision in ULPs (units in the last place)
            return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp
                    // unless the result is subnormal
                    || std::fabs(x-y) < std::numeric_limits<double>::min();
        };


        std::function<bool(vertex, vertex, double)> are_parallel = [are_double_equal, ulp](vertex v1, vertex v2, double alpha) -> bool {
            if(!are_double_equal(v1.x, alpha * v2.x, 3)) return false;
            if(!are_double_equal(v1.y, alpha * v2.y, 3)) return false;
            if(!are_double_equal(v1.z, alpha * v2.z, 3)) return false;
            return true;
        };

        return are_parallel(ab, cd, get_alpha(ab, cd))
                && are_parallel(bc, da, get_alpha(bc, da))
                && ! are_parallel(ab, bc, get_alpha(ab, bc));
    }

}


