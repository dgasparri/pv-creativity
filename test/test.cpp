#include "../src/panel_geometry_fp.h"
#include <iostream>
#include <functional>
#include <cmath>

#define M_PI 3.1415


void print_v(p_geometry::vertex i) {
    std::cout<<"Vertex x: "<<i.x<<" y: "<<i.y<<" z: "<<i.z<<std::endl;
}

void print_pl(p_geometry::plane i) {
    std::cout<<"Plane a_x: "<<i.a_x<<" a_y: "<<i.a_y<<" a_z: "<<i.a_z<<" d: "<<i.d<<std::endl;
}


void test_vertex_intersection() {
    p_geometry::vertex a(1,1,1);
    p_geometry::vertex b(1,2,1);
    p_geometry::vertex c(2,2,1);
    p_geometry::vertex d(2,1,1);

    p_geometry::vertex i = p_geometry::diagonal_intersection(a, b, c, d, 3);
    print_v(i);

    p_geometry::plane pl = p_geometry::plane_from_vertices(a, b, d);
    p_geometry::vertex n = p_geometry::plane_normal(pl);
    print_pl(pl);
    print_v(n);

    std::cout<<"Beta: "<< (p_geometry::beta_rad(pl) * 180 / M_PI) <<std::endl;
    std::cout<<"Z_S: "<< (p_geometry::Z_S_rad(pl) * 180 / M_PI) <<std::endl;


    /* Piano inclinato est */

    p_geometry::vertex e(0,0,0);
    p_geometry::vertex f(0,5,0);
    p_geometry::vertex g(5,5,5);
    p_geometry::vertex h(5,0,5);

    p_geometry::vertex j = p_geometry::diagonal_intersection(e, f, g, h, 3);
    print_v(j);

    p_geometry::plane pl2 = p_geometry::plane_from_vertices(e, f, h);
    print_pl(pl2);
    std::cout<<"Punto g sul piano? "<<p_geometry::is_vertex_on_plane(pl2, g)<<std::endl;
    p_geometry::vertex o = p_geometry::plane_normal(pl2);
    print_v(o);

    std::cout<<"Beta: "<< (p_geometry::beta_rad(pl2) * 180 / M_PI) <<std::endl;
    std::cout<<"Z_S: "<< (p_geometry::Z_S_rad(pl2) * 180 / M_PI) <<std::endl;
}


void test_is_plane()
{

    p_geometry::vertex a(1,1,1);
    p_geometry::vertex b(1,2,1);
    p_geometry::vertex c(2,2,1);
    p_geometry::vertex d(2,1,1);

    p_geometry::plane p = p_geometry::plane_from_vertices(a, b, d);

    if(p_geometry::is_vertex_on_plane(p, c, 3)) {
        std::cout<<"Plane a_x: "<<p.a_x<<" a_y: "<<p.a_y<<" a_z: "<<p.a_z<<" d: "<<p.d<<std::endl;
    } else {
        std::cout<<"Is not a plane";
    }


    p_geometry::vertex e(1,1,1);
    p_geometry::vertex f(1,2,3);
    p_geometry::vertex g(2,2,1);
    p_geometry::vertex h(2,1,1);

    p_geometry::plane p2 = p_geometry::plane_from_vertices(e, f, h);

    if(p_geometry::is_vertex_on_plane(p2, g, 3)) {
        std::cout<<"Plane a_x: "<<p2.a_x<<" a_y: "<<p2.a_y<<" a_z: "<<p2.a_z<<" d: "<<p2.d<<std::endl;
    } else {
        std::cout<<"Is not a plane";
    }
}
void test_is_valid_parallelogram()
{
    p_geometry::vertex a(1,1,1);
    p_geometry::vertex b(1,2,1);
    p_geometry::vertex c(2,2,1);
    p_geometry::vertex d(2,1,1);


    p_geometry::vertex ab = b - a;
    p_geometry::vertex bc = c - b;
    p_geometry::vertex cd = d - c;
    p_geometry::vertex da = a - d;

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

*/
    std::cout<<"ab_cd_iszero "<<(ab.y * cd.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(ab.z * cd.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(bc.y * da.x)<<std::endl;
    std::cout<<"ab_cd_iszero "<<(bc.z * da.x)<<std::endl;

    std::cout<<"Is valid parallelogram? (exp. 1) "<<p_geometry::is_valid_parallelogram(a, b, c, d, 3)<<std::endl;

    p_geometry::vertex e(1,1,1);
    p_geometry::vertex f(1,2,2);
    p_geometry::vertex g(2,3,1);
    p_geometry::vertex h(2,1,1);

    std::cout<<"Is valid parallelogram? (exp. 0) "<<p_geometry::is_valid_parallelogram(e, f, g, h, 3)<<std::endl;;



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


int main()
{
    //test_is_valid_parallelogram();
    //test_is_plane();
    //test_vertex_intersection();
    test_load_vertex();
}
 