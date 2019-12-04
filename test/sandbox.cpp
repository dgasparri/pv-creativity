#include "../src/config.h"
#include "../src/lib/geometry_fp.h"

#include <functional>
#include <vector>

#include <cmath>


#include <iostream>

struct vertex {
    const double x;
    const double y;
    const double z;
};

const std::vector<vertex> test_vertices()
{
    std::vector<vertex> vertices;
    vertices.push_back(vertex {-3.0, -3.0, 0.0});
    vertices.emplace_back(vertex{3.0, -3.0, 0.0});
    vertices.emplace_back(vertex{0.0, 0.0, 1.5});
    return vertices;
}

class PanelView {
    std::vector<vertex> vertices;
    std::vector<vertex> *vpointer;
public:

    //[1] PanelView(const std::vector<vertex>& vertices): vertices(vertices) {};
    //[2] void setVertices(const std::vector<vertex>& v)  {vertices = v;  };
    //[2 bis] void setVertices(std::vector<vertex> v)  {vertices = v;  };
    //[3] void setVerticesPointer(std::vector<vertex> *v)  {vpointer = v;  };
    void draw() {std::cout<<vertices[0].x; };
    void drawp() {std::cout<<(*vpointer)[0].x; };
};

struct ab {
    int a;
};

int main()
{

    std::vector<vertex> panel_vertices = test_vertices();
    
    //[1] Works fine
    //PanelView pv(panel_vertices);
    //pv.draw();

    //[2 and 2 bis] - Error C2280: 'vertex &vertex::operator =(const vertex &)': deleted
    //PanelView pv;
    //pv.setVertices(panel_vertices);

    //[3] - OK
    /*
    PanelView pv;
    pv.setVerticesPointer(&panel_vertices);
    pv.drawp();
    */

    const ab t {1};
    std::cout<<t.a;
    ab *t2 = (ab*) &t;
    t2->a = 2; //test/sandbox.cpp(67): error C2166: l'elemento l-value specifica un oggetto const
    std::cout<<t2->a;

    //std::cout<<panel_vertices[0].x;
}
 