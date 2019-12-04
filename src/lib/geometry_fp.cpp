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

    bool vertex::operator==(const vertex& other) const {
        return std::fabs(x - other.x) < EQUAL_COORDINATES_EPSILON
            && std::fabs(y - other.y) < EQUAL_COORDINATES_EPSILON
            && std::fabs(z - other.z) < EQUAL_COORDINATES_EPSILON;
        //return are_double_equal(x, other.x, 3) 
        //    && are_double_equal(y, other.y, 3)
        //    && are_double_equal(z, other.z, 3);
    }

    std::ostream& operator<<(std::ostream& os, const vertex& v)
    {
        os << "<" << v.x << "," << v.y << "," << v.z <<  ">";
        return os;
    }

    

    plane::plane(double a_x, double a_y, double a_z, double d):
        a_x(a_x), a_y(a_y), a_z(a_z), d(d) {}

    std::ostream& operator<<(std::ostream& os, const plane& pl)
    {
        os << "pl(<" << pl.a_x << "," << pl.a_y << "," << pl.a_z <<  ">,"<< pl.d <<")";
        return os;
    }

    //Serve plane horizon?
    triangle::triangle(const vertex a, const vertex b, const vertex c):
		mZ_S_rad(fZ_S_rad(fplane(a, b, c))),
		marea(farea(a, b, c)),
        mplane_normal(fnormal(fplane(a, b, c))),
        mbeta_rad(fbeta_rad(a, b, c, fZ_S_rad(fplane(a, b, c))))
	{
    }


    // Returns the plane
    // Throw exception if vertices is not in plane
    pure plane fplane(const vertex a, const vertex b, const vertex d)
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


    pure vertex fnormal(const plane pl) 
    {
        return vertex(pl.a_x, pl.a_y, pl.a_z);
    }

    pure vertex rotate_vertex_zaxis(const vertex v, const double angle_rad)
    {
        return vertex(
				v.x * cos(angle_rad) - v.y * sin(angle_rad),
				v.x * sin(angle_rad) + v.y * cos(angle_rad),
				v.z
			);
    }

    pure plane rotate_plane_zaxis(const vertex a, const vertex b, const vertex d, const double angle)
    {
		return fplane(
            rotate_vertex_zaxis(a, angle), 
            rotate_vertex_zaxis(b, angle), 
            rotate_vertex_zaxis(d, angle));
    }

    //Check direction
    pure plane_xparallel rotate_plane_to_xparallel(const vertex a, const vertex b, const vertex d, const Z_S_rad Z_S_rad)
    {
        return rotate_plane_zaxis(
            a,
            b,
            d,
            -Z_S_rad
        );
    }


	//Positive - direction south
	//Negative - direction north
    pure double fbeta_rad(const vertex a, const vertex b, const vertex d, const Z_S_rad Z_S) 
    {

        const plane_xparallel mpl_xparallel = rotate_plane_to_xparallel(a, b, d, Z_S);
		if (are_double_equal(mpl_xparallel.a_z, 0, 3)) {
			return M_PI/2;
		}
		return atan( - mpl_xparallel.a_y / mpl_xparallel.a_z);
    }

    // X è ovest-est, con negativi è ovest
    pure double fZ_S_rad(const plane pl) 
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

    pure double fnorm(const vertex pl)
    {
        return sqrt(
            std::pow(pl.x,2) +
            std::pow(pl.y,2) +
            std::pow(pl.z,2)
            ) ;
    }

    pure m_squared farea(const vertex a, const vertex b, const vertex c)
    {
        // See https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle
        vertex ab = b - a;
        vertex ac = c - a;
        double ab_ac_norm_product = fnorm(ab) * fnorm(ac);
        double ab_ac_dot_product = ab.x * ac.x + ab.y * ac.y + ab.z * ac.z ;
        double cos_theta = ab_ac_dot_product / ab_ac_norm_product;
        double sin_theta = std::sqrt(1-std::pow(cos_theta,2));
        return ab_ac_norm_product * sin_theta / 2;
    }
}


