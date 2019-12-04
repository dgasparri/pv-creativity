#define _USE_MATH_DEFINES
#include "catch.hpp"
#include <iostream>
#include <vector>

#include "../src/lib/geometry_fp.h"
#include "../src/config.h"



TEST_CASE( "Vertex", "[vertex]" ) {
	geometry::vertex v1(-3.0, -3.0, 0.0);
	geometry::vertex v3(0.0, 0.0, 3.0);

	SECTION("Basic operation") {
		REQUIRE( v1 == v1 );
		REQUIRE( v1 == geometry::vertex(-3.0 + EQUAL_COORDINATES_EPSILON/10, -3.0, 0.0) );
		REQUIRE( v1 == geometry::vertex(-3.0 - EQUAL_COORDINATES_EPSILON/10, -3.0, 0.0) );
		REQUIRE( !(v1 == geometry::vertex(-3.0 + EQUAL_COORDINATES_EPSILON * 2, -3.0, 0.0)) );
		REQUIRE( !(v1 == geometry::vertex(-3.0 - EQUAL_COORDINATES_EPSILON * 2, -3.0, 0.0)) );
		REQUIRE( (v3 - v1) == geometry::vertex(3.0, 3.0, 3.0) );
	}

	SECTION("Rotation") {
		// -sqrt(2* pow(3.0,2)) : radius triangle (-4.24264)
		geometry::vertex v1_r45(0.0, -sqrt(2* pow(3.0,2)), 0.0);
		geometry::vertex v1_r90(3.0, -3.0, 0.0);
		geometry::vertex v1_rm90(-3.0, 3.0, 0.0);
		geometry::vertex v1_r180(3.0, 3.0, 0.0);

		REQUIRE( v1_r45  == geometry::rotate_vertex_zaxis(v1, M_PI_4 ) );
		REQUIRE( v1_r90  == geometry::rotate_vertex_zaxis(v1, M_PI_2) );
		REQUIRE( v1_rm90 == geometry::rotate_vertex_zaxis(v1, -M_PI_2) );
		REQUIRE( v1_r180 == geometry::rotate_vertex_zaxis(v1, M_PI) );
		REQUIRE( v1_r180 == geometry::rotate_vertex_zaxis(v1, -M_PI) );
		REQUIRE( v3  == geometry::rotate_vertex_zaxis(v3, M_PI_4 ) );
		REQUIRE( v3  == geometry::rotate_vertex_zaxis(v3, M_PI_2) );
	}

}

TEST_CASE( "Plane", "[plane]" ) {
	//Y parallel
	geometry::vertex v1(-3.0, -3.0, 0.0);
	geometry::vertex v2(3.0, -3.0, 0.0);
	geometry::vertex v3(0.0, 0.0, 3.0);

	geometry::plane pl1 = geometry::fplane(v1, v2, v3);
	geometry::plane pl2 = geometry::fplane(v2, v1, v3);
	geometry::plane pl3 = geometry::fplane(v3, v1, v2);
	auto onplane = [](geometry::plane pl, geometry::vertex v) -> bool {
		return (pl.a_x * v.x + pl.a_y * v.y + pl.a_z * v.z - pl.d) 
				< (EQUAL_COORDINATES_EPSILON * 3);
	};

	SECTION("Plane creation") {
		REQUIRE( onplane(pl1, v1));
		REQUIRE( onplane(pl1, v2));
		REQUIRE( onplane(pl1, v3));
		REQUIRE( onplane(pl2, v1));
		REQUIRE( onplane(pl3, v1));
	}


}


TEST_CASE("Triangle", "[triangle]") {
	//Y parallel
	geometry::vertex v1(-3.0, -3.0, 0.0);
	geometry::vertex v2(3.0, -3.0, 0.0);
	geometry::vertex v3(0.0, 0.0, 3.0);


	SECTION("Area") {
        //v2.x - v1.x
        double base = 6.0;
        double height = std::sqrt(std::pow(3.0, 2) + std::pow(3.0, 2));
        double area = base * height / 2;
		REQUIRE( geometry::farea(v1, v2, v3) > 12); //12.7279220614
        REQUIRE( geometry::farea(v2, v1, v3) > 12); //12.7279220614
        REQUIRE( std::fabs(area - geometry::farea(v1, v2, v3))
                  < (EQUAL_COORDINATES_EPSILON * 3)); 
        REQUIRE( std::fabs(area - geometry::farea(v2, v1, v3))
                  < (EQUAL_COORDINATES_EPSILON * 3)); 

	}


}

/*


void test_vertex_intersection() {
    geometry::vertex a(1,1,1);
    geometry::vertex b(1,2,1);
    geometry::vertex c(2,2,1);
    geometry::vertex d(2,1,1);

    geometry::vertex i = geometry::diagonal_intersection(a, b, c, d, 3);
    print_v(i);

    geometry::plane pl = geometry::plane_from_vertices(a, b, d);
    geometry::vertex n = geometry::plane_normal(pl);
    print_pl(pl);
    print_v(n);

    std::cout<<"Beta: "<< (geometry::beta_rad(pl) * 180 / M_PI) <<std::endl;
    std::cout<<"Z_S: "<< (geometry::Z_S_rad(pl) * 180 / M_PI) <<std::endl;


    /* Piano inclinato est * /

    geometry::vertex e(0,0,0);
    geometry::vertex f(0,5,0);
    geometry::vertex g(5,5,5);
    geometry::vertex h(5,0,5);

    geometry::vertex j = geometry::diagonal_intersection(e, f, g, h, 3);
    print_v(j);

    geometry::plane pl2 = geometry::plane_from_vertices(e, f, h);
    print_pl(pl2);
    std::cout<<"Punto g sul piano? "<<geometry::is_vertex_on_plane(pl2, g)<<std::endl;
    geometry::vertex o = geometry::plane_normal(pl2);
    print_v(o);

    std::cout<<"Beta: "<< (geometry::beta_rad(pl2) * 180 / M_PI) <<std::endl;
    std::cout<<"Z_S: "<< (geometry::Z_S_rad(pl2) * 180 / M_PI) <<std::endl;
}


void test_is_plane()
{

    geometry::vertex a(1,1,1);
    geometry::vertex b(1,2,1);
    geometry::vertex c(2,2,1);
    geometry::vertex d(2,1,1);

    geometry::plane p = geometry::plane_from_vertices(a, b, d);

    if(geometry::is_vertex_on_plane(p, c, 3)) {
        std::cout<<"Plane a_x: "<<p.a_x<<" a_y: "<<p.a_y<<" a_z: "<<p.a_z<<" d: "<<p.d<<std::endl;
    } else {
        std::cout<<"Is not a plane";
    }


    geometry::vertex e(1,1,1);
    geometry::vertex f(1,2,3);
    geometry::vertex g(2,2,1);
    geometry::vertex h(2,1,1);

    geometry::plane p2 = geometry::plane_from_vertices(e, f, h);

    if(geometry::is_vertex_on_plane(p2, g, 3)) {
        std::cout<<"Plane a_x: "<<p2.a_x<<" a_y: "<<p2.a_y<<" a_z: "<<p2.a_z<<" d: "<<p2.d<<std::endl;
    } else {
        std::cout<<"Is not a plane";
    }
}
void test_is_valid_parallelogram()
{
    geometry::vertex a(1,1,1);
    geometry::vertex b(1,2,1);
    geometry::vertex c(2,2,1);
    geometry::vertex d(2,1,1);


    geometry::vertex ab = b - a;
    geometry::vertex bc = c - b;
    geometry::vertex cd = d - c;
    geometry::vertex da = a - d;

/*
    ab.print();
    bc.print();
    cd.print();
    da.print();
    std::cout<<"ab bc "<<get_alpha(ab, bc)<<std::endl;
    std::cout<<"ab cd "<<get_alpha(ab, cd)<<std::endl;
    std::cout<<"bc cd "<<get_alpha(bc, cd)<<std::endl;
    std::cout<<"bc da "<<get_alpha(bc, da)<<std::endl;
    std::cout<<"cd da "<<get_alpha(cd, da)<<std::endl<<std::endl;


    std::cout<<"ab bc "<<parallel(ab, bc, get_alpha(ab, bc))<<std::endl;
    std::cout<<"ab cd "<<parallel(ab, cd, get_alpha(ab, cd))<<std::endl;
    std::cout<<"bc cd "<<parallel(bc, cd, get_alpha(bc, cd))<<std::endl;
    std::cout<<"bc da "<<parallel(bc, da, get_alpha(bc, da))<<std::endl;
    std::cout<<"cd da "<<parallel(cd, da, get_alpha(cd, da))<<std::endl;

* /
    std::cout<<"ab_cd_iszero "<<(ab.y * cd.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(ab.z * cd.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(bc.y * da.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(bc.z * da.x)<<std::endl;

    std::cout<<"Is valid parallelogram? (exp. 1) "<<geometry::is_valid_parallelogram(a, b, c, d, 3)<<std::endl;

    geometry::vertex e(1,1,1);
    geometry::vertex f(1,2,2);
    geometry::vertex g(2,3,1);
    geometry::vertex h(2,1,1);

    std::cout<<"Is valid parallelogram? (exp. 0) "<<geometry::is_valid_parallelogram(e, f, g, h, 3)<<std::endl;;



}


#include <stdio.h>
#include <stdlib.h>
void test_load_vertex()
{
    float v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
    FILE *fp;
    fp = fopen ("C:/Users/dmg/C++/repos/pv-creativity/geometries/triangles.csv", "r");
    for(int i=0; i<9; i++) {
        fscanf(fp, "%f %f %f, %f %f %f, %f %f %f\n", &v1x, &v1y, &v1z, &v2x, &v2y, &v2z, &v3x, &v3y, &v3z);
        std::cout<<"X: "<<v1x<<" Y: "<<v1y<<" Z: "<<v1z<<std::endl;
        std::cout<<"X: "<<v2x<<" Y: "<<v2y<<" Z: "<<v2z<<std::endl;
        std::cout<<"X: "<<v3x<<" Y: "<<v3y<<" Z: "<<v3z<<std::endl;
    }
    fclose(fp);
}

*/

/*
void test_rotation() {
			auto rotz = [](geometry::vertex v, double q)->geometry::vertex {
			return geometry::vertex(
				v.x * cos(q) - v.y * sin(q),
				v.x * sin(q) + v.y * cos(q),
				v.z
			);
		};


		geometry::vertex v1prime = rotz(*v[i+0], -tr.Z_S_rad);
		geometry::vertex v2prime = rotz(*v[i+1], -tr.Z_S_rad);
		geometry::vertex v3prime = rotz(*v[i+2], -tr.Z_S_rad);
		p_v("v1 prime ", v1prime);
		p_v("v2 prime ", v2prime);
		p_v("v3 prime ", v3prime);
		geometry::plane plprime = geometry::plane_from_vertices(v1prime, v2prime, v3prime);
		std::cout << "pl prime: a_x: " << plprime.a_x << " a_y: " << plprime.a_y << " a_z: " << plprime.a_z << " d: " << plprime.d << std::endl;
		//geometry::triangle trprime = geometry::triangle(v1prime, v2prime, v3prime);
		double b= geometry::beta_rad_from_plane(
			geometry::rotate_plane_to_xparallel(
                    v1prime, v2prime, v3prime, 0.0));

		std::cout << "beta controllo: " << b* 180 / M_PI << " Z_S: " << 
			Z_S_rad_from_plane(plane_from_vertices(v1prime, v2prime, v3prime)) * 180 / M_PI  << std::endl;


}

void test_planes() {
	std::vector<geometry::vertex*> v = panel_io::test_vertices();
	for (int i = 0; i + 2 < v.size(); i += 3) {
		std::cout << "Triangolo " << i << std::endl;
		print_vertex("a ", *v[i+0]);
		print_vertex("b ", *v[i+1]);
		print_vertex("c ", *v[i + 2]);
		print_vertex("ab", *v[i + 1] - *v[i + 0]);
		print_vertex("ac", *v[i + 2] - *v[i + 0]);
		geometry::plane pl = geometry::plane_from_vertices(*v[i + 0], *v[i + 1], *v[i + 2]);
		std::cout << "plane: a_x: " << pl.a_x << " a_y: " << pl.a_y << " a_z: " << pl.a_z << " d: " << pl.d << std::endl;
		
		geometry::triangle tr = geometry::triangle(*v[i + 0], *v[i + 1], *v[i + 2]);
		std::cout << " x/y(opposto-adiacente, a_y/a_x) " << pl.a_y / pl.a_x << std::endl;
		std::cout << "tr: beta: " << tr.beta_rad * 180 / M_PI << " Z_S: " << tr.Z_S_rad * 180 / M_PI << " area: " << tr.area << std::endl;
		std::cout<<std::endl << std::endl;

	}
}
*/