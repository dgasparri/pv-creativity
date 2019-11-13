#include <vector>
#include "../src/Cell.h"
#include "../src/panel_geometry_fp.h"


void initTest() {
    p_geometry::vertex a(-10, 10, 10);
    p_geometry::vertex b(10, 10, 10);
    p_geometry::vertex c(10, 0, 0);
    p_geometry::vertex d(-10, 0, 0);
    
    Cell cell(a, b, c, d);

    std::vector<Cell> vt;
    vt.push_back(cell);
    //vt.append(cell);
    
    Panel panel(vt, 44);        
}