#include "../src/panel_geometry_fp.h"
#include <iostream>




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


int main()
{
    test_is_valid_parallelogram();
}
 