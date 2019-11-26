#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>

#include "../src/lib/geometry_fp.h"

void print_vertex(const char *s, geometry::vertex v) {
	std::cout<<s<<": ("<<v.x<<","<<v.y<<","<<v.z<<")"<<std::endl;
}


const std::vector<geometry::vertex *> panel_io::test_vertices()
{
	std::vector<geometry::vertex *> vertices;

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	return vertices;

}


void test_rotationx() {
	std::vector<geometry::vertex*> v = panel_io::test_vertices();
	for(geometry vertex *vp: v) {
		print_vertex("v           ",*vp);
		print_vertex("v rotated 45",geometry::rotate_zaxis(*vp, 45 * M_PI / 180));
	}
}


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