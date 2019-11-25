#include "panel_geometry_fp.h"



pure bool are_double_equal(double x, double y, int ulp)
{    
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp
            // unless the result is subnormal
            || std::fabs(x-y) < std::numeric_limits<double>::min();
}



namespace p_geometry {

    
    vertex::vertex(double x, double y, double z):
            x(x), y(y), z(z) {}

    vertex vertex::operator-(const vertex& other) const {
        return vertex(x-other.x, y-other.y, z-other.z);
    }
    

    plane::plane(double a_x, double a_y, double a_z, double d):
        a_x(a_x), a_y(a_y), a_z(a_z), d(d) {}

    //Serve plane horizon?
    triangle::triangle(const vertex a, const vertex b, const vertex c):
		beta_rad (p_geometry::beta_rad(plane_from_vertices(a, b, c))),
		Z_S_rad (p_geometry::Z_S_rad(plane_from_vertices(a, b, c))),
		area(vector_norm(plane_normal(plane_from_vertices(a, b, c))) / 2)
	{
        //plane pl = plane_from_vertices(a, b, c);
        //beta_rad = p_geometry::beta_rad(pl);
        //Z_S_rad = p_geometry::Z_S_rad(pl);
        //Area of a triangle from vectors a, b, c: 1/2 ||ab x ac||
        //area = vector_norm(plane_normal(pl))/2;
    }


    // Returns the plane
    // Throw exception if vertices is not in plane
    pure plane plane_from_vertices(const vertex a, const vertex b, const vertex d)
    {
        vertex ab = b - a;
        vertex da = d - a;

        //Normal to the plane
        double a_x = ab.y*da.z - ab.z*da.y;
        double a_y = -(ab.x*da.z - ab.z*da.x);
        double a_z = ab.x*da.y - ab.y*da.x;

        //Plane equation a_x * x + a_y * y + a_z * z = d
        return plane(a_x, a_y, a_z, a_x * a.x + a_y * a.y + a_z * a.z);
    }


    pure vertex plane_normal(const plane pl) 
    {
        return vertex(pl.a_x, pl.a_y, pl.a_z);
    }


    pure double beta_rad(const plane pl) 
    {
        //Horizontal plane is 0x+0y+1z = 0
        double cos_beta = pl.a_z / sqrt(pow(pl.a_x,2)+pow(pl.a_y,2) + pow(pl.a_z,2));
        return acos(cos_beta);
    }

    // X è ovest-est, con negativi è ovest
    // Quindi deve essere parallelo a y (nord-sud) per essere a zero
    pure double Z_S_rad(const plane pl) 
    {
        //nord-sud plane is 0x+1y+0z = 0
        double cos_Z_S = pl.a_y / sqrt(pow(pl.a_x,2)+pow(pl.a_y,2) + pow(pl.a_z,2));
        return acos(cos_Z_S);
    }

    pure double vector_norm(const vertex pl_normal)
    {
        return sqrt(
            std::pow(pl_normal.x,2) +
            std::pow(pl_normal.y,2) +
            std::pow(pl_normal.z,2)
            ) / 2;
    }

}


