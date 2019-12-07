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

int somma_abcd(int a, int b)
{
    std::cout<<"A: "<<a<<" B: "<<b<<std::endl;
    return a + b;
}

/*
int main()
{
    int** a;
    a = []()->int** {
        int** c = new int* [2];
        
        c[0] = new int[2]{3,4};
        c[1] = new int[2]{9,8};
        

        //int c[2][2] = ;
        //return (int **)c;
        return c;
    }(); 
    //int b[2][2] = &a;
    std::cout<<"a: "<<a[1][0];
    return 0;
    auto somma_bc = [](int b)->int{return somma_abcd(3, b);};
    std::cout<<somma_bc(5)<<std::endl;
    return 0;
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
    * /

    const ab t {1};
    std::cout<<t.a;
    ab *t2 = (ab*) &t;
    t2->a = 2; //test/sandbox.cpp(67): error C2166: l'elemento l-value specifica un oggetto const
    std::cout<<t2->a;

    //std::cout<<panel_vertices[0].x;
}
 */

#include <iostream>
#include <cmath>
#include "discpp.h"

double zmat[50][50];

int main ()
{ int n = 50 ,i, j;
  double fpi = 3.1415927 / 180.0, step, x, y;
  const char *ctit1 = "Surface Plot (SURMAT)",
             *ctit2 = "F(X,Y) = 2*SIN(X)*SIN(Y)";
  Dislin g;

  step = 360.0 / (n - 1);
  for (i = 0; i < n; i++)
  { x = i * step;
    for (j = 0; j < n; j++)
    { y = j * step;
      zmat[i][j] = 2 * sin (x * fpi) *sin(y * fpi);
    }
  }

  g.scrmod ("revers");
  g.setpag ("da4p");
  g.metafl ("cons");
  g.disini ();
  g.pagera ();
  g.complx ();
  g.axspos (200, 2600);
  g.axslen (1800, 1800);

  g.name   ("X-axis", "x");
  g.name   ("Y-axis", "y");
  g.name   ("Z-axis", "z");

  g.titlin (ctit1, 2);
  g.titlin (ctit2, 4);

  g.view3d (-5.0, -5.0, 4.0, "abs");
  g.graf3d (0.0, 360.0, 0.0, 90.0, 0.0, 360.0, 0.0, 90.0,
            -3.0, 3.0, -3.0, 1.0);
  g.height (50);
  g.title  ();

  g.color  ("green");
  g.surmat ((double *) zmat, 50, 50, 1, 1);
  g.disfin ();
  return 0;
}