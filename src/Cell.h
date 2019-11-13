#include <vector>
#include "panel_geometry_fp.h"

using namespace p_geometry;

class Cell {
    const vertex a, b, c, d;
    double beta, Z_S;
    double area;

    Cell(vertex a, vertex b, vertex c, vertex d):
        a(a), b(b), c(c), d(d) {}
public:
    void setArea();
    void getArea();
    void setVertices();
};

class Panel {
    std::vector<Cell> cells;
    double latitude;
    Panel(std::vector<Cell> cells, double latitude): 
        cells(cells), latitude(latitude) {}

    
}

