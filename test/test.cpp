#include "src/panel_geometry_fp.h"
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


int main()
{
    vertex a(0,0,0);
    vertex b(0,1,0);
    vertex c(1,1,0);
    vertex d(1,0,0);


    vertex ab = b - a;
    vertex bc = c - b;
    vertex cd = d - c;
    vertex da = a - d;
    std::cout<<"ab.y "<<ab.y<<std::endl;
}