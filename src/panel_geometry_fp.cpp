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



        std::function<bool(vertex, vertex, double)> are_parallel = [ulp](vertex v1, vertex v2, double alpha) -> bool {
            if(!are_double_equal(v1.x, alpha * v2.x, 3)) return false;
            if(!are_double_equal(v1.y, alpha * v2.y, 3)) return false;
            if(!are_double_equal(v1.z, alpha * v2.z, 3)) return false;
            return true;
        };

        return are_parallel(ab, cd, get_alpha(ab, cd))
                && are_parallel(bc, da, get_alpha(bc, da))
                && ! are_parallel(ab, bc, get_alpha(ab, bc));
    }

    // Returns the plane
    // Throw exception if vertices is not in plane
    pure plane plane_from_vertices(vertex a, vertex b, vertex d)
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

    pure bool is_vertex_on_plane(plane pl, vertex c, int ulp) 
    {
        return are_double_equal(pl.a_x*c.x + pl.a_y*c.y + pl.a_z*c.z, pl.d, ulp ); 
    }

    pure vertex plane_normal(plane pl) 
    {
        return vertex(pl.a_x, pl.a_y, pl.a_z);
    }

    pure vertex diagonal_intersection(vertex a, vertex b, vertex c, vertex d, int ulp) 
    {
        vertex ca = c-a;
        vertex db = d-b;
        
        double t;
        bool line_ca = false;
        bool s_ba_x = !isnan(db.x/ca.x);
        bool s_ba_y = !isnan(db.y/ca.y);
        bool s_ba_z = !isnan(db.z/ca.z);
        bool s_ab_x = !isnan(ca.x/db.x);
        bool s_ab_y = !isnan(ca.y/db.y);
        bool s_ab_z = !isnan(ca.z/db.z);


        bool s_ba_xy = (s_ba_x && s_ba_y)? !are_double_equal(db.x/ca.x - db.y/ca.y, 0.0, ulp) : false;
        bool s_ba_xz = (s_ba_x && s_ba_z)? !are_double_equal(db.x/ca.x - db.z/ca.z, 0.0, ulp) : false;
        bool s_ba_yz = (s_ba_y && s_ba_z)? !are_double_equal(db.y/ca.y - db.z/ca.z, 0.0, ulp) : false;

        bool s_ab_xy = (s_ab_x && s_ab_y)? !are_double_equal(ca.x/db.x - ca.y/db.y, 0.0, ulp) : false;
        bool s_ab_xz = (s_ab_x && s_ab_z)? !are_double_equal(ca.x/db.x - ca.z/db.z, 0.0, ulp) : false;
        bool s_ab_yz = (s_ab_y && s_ab_z)? !are_double_equal(ca.y/db.y - ca.z/db.z, 0.0, ulp) : false;


        std::function<void(double, double, double, double, double, double, double, double)> s_t 
                = [&t](double a_x, double  b_x, double  a_y, double  b_y, double  ca_x,double  ca_y, double db_x, double db_y) 
                {
                    t = (b_x - a_x)/ca_x - (b_y - a_y)/ca_y; //N1 - N2
                    t /= (db_y/ca_y - db_x/ca_x);
                    //t = (b_x - a_x)/ca_x + s * db_x / ca_x;

                };

        if(s_ba_xy) {
            s_t(a.x, b.x, a.y, b.y, ca.x, ca.y, db.x, db.y);
            line_ca = false;
        } 
        else if (s_ba_xz) {
            s_t(a.x, b.x, a.z, b.z, ca.x, ca.z, db.x, db.z);
            line_ca = false;
        } 
        else if (s_ba_yz) {
            s_t(a.y, b.y, a.z, b.z, ca.y, ca.z, db.y, db.z);
            line_ca = false;
        }
        else if(s_ab_xy) {
            s_t(b.x, a.x, b.y, a.y, db.x, db.y, ca.x, ca.y);
            line_ca = true;
        } 
        else if (s_ab_xz) {
            s_t(b.x, a.x, b.z, a.z, db.x, db.z, ca.x, ca.z);
            line_ca = true;
        } 
        else if (s_ab_yz) {
            s_t(b.y, a.y, b.z, a.z, db.y, db.z, ca.y, ca.z);
            line_ca = true;
        } else {
            throw "I vettori sono paralleli";
        }

        if (line_ca) {
            return vertex(a.x + t*ca.x, a.y + t*ca.y, a.z + t*ca.z);
        } else {
            return vertex(b.x + t*db.x, b.y + t*db.y, b.z + t*db.z);
        }
    }

    pure double beta_rad(plane pl) 
    {
        //Horizontal plane is 0x+0y+1z = 0
        double cos_beta = pl.a_z / sqrt(pow(pl.a_x,2)+pow(pl.a_y,2) + pow(pl.a_z,2));
        return acos(cos_beta);
    }

    // X è ovest-est, con negativi è ovest
    // Quindi deve essere parallelo a y (nord-sud) per essere a zero
    pure double Z_S_rad(plane pl) 
    {
        //nord-sud plane is 0x+1y+0z = 0
        double cos_Z_S = pl.a_y / sqrt(pow(pl.a_x,2)+pow(pl.a_y,2) + pow(pl.a_z,2));
        return acos(cos_Z_S);
    }

}


