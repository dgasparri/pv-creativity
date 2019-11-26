#include "geometry_fp.h"



pure bool are_double_equal(double x, double y, int ulp)
{    
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp
            // unless the result is subnormal
            || std::fabs(x-y) < std::numeric_limits<double>::min();
}



namespace geometry {

    
    vertex::vertex(double x, double y, double z):
            x(x), y(y), z(z) {}

    vertex vertex::operator-(const vertex& other) const {
        return vertex(x-other.x, y-other.y, z-other.z);
    }
    

    plane::plane(double a_x, double a_y, double a_z, double d):
        a_x(a_x), a_y(a_y), a_z(a_z), d(d) {}

    //Serve plane horizon?
    triangle::triangle(const vertex a, const vertex b, const vertex c):
		Z_S_rad(Z_S_rad_from_plane(plane_from_vertices(a, b, c))),
		area(1),
        plane_normal(normal_vector_from_plane(plane_from_vertices(a, b, c))),
        beta_rad(
			beta_rad_from_plane(
				rotate_plane_to_xparallel(
					a, b, c,
					Z_S_rad_from_plane(plane_from_vertices(a, b, c))
				))
            )
	{
        //plane pl = plane_from_vertices(a, b, c);
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


    pure vertex normal_vector_from_plane(const plane pl) 
    {
        return vertex(pl.a_x, pl.a_y, pl.a_z);
    }

    pure vertex rotate_zaxis(const vertex v, const double angle)
    {
        return vertex(
				v.x * cos(angle) - v.y * sin(angle),
				v.x * sin(angle) + v.y * cos(angle),
				v.z
			);
    }

    pure plane plane_rotate_zaxis(const vertex a, const vertex b, const vertex d, const double angle)
    {
		return plane_from_vertices(
            rotate_zaxis(a, angle), 
            rotate_zaxis(b, angle), 
            rotate_zaxis(d, angle));
    }

    //Check direction
    pure plane_xparallel rotate_plane_to_xparallel(const vertex a, const vertex b, const vertex d, const Z_S_rad Z_S_rad)
    {
        return plane_rotate_zaxis(
            a,
            b,
            d,
            -Z_S_rad
        );
    }


	//Positive - direction south
	//Negative - direction north
    pure double beta_rad_from_plane(const plane_xparallel pl) 
    {
		if (are_double_equal(pl.a_z, 0, 3)) {
			return M_PI/2;
		}
		return atan( - pl.a_y / pl.a_z);
    }

    // X è ovest-est, con negativi è ovest
    pure double Z_S_rad_from_plane(const plane pl) 
    {
		// y/x
		if (are_double_equal(pl.a_y, 0.0, 3)) {
			if (pl.a_x > 0)
				return -M_PI / 2; //Points from est to west
			else
				return M_PI / 2; //Points from west to east
		}

		return atan(pl.a_x / pl.a_y);
        
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


