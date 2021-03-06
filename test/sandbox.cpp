// #include "../src/global.h"
// #include "../src/lib/geometry_fp.h"

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
    */

    const ab t {1};
    std::cout<<t.a;
    ab *t2 = (ab*) &t;
    t2->a = 2; //test/sandbox.cpp(67): error C2166: l'elemento l-value specifica un oggetto const
    std::cout<<t2->a;

    //std::cout<<panel_vertices[0].x;
}
 



 //Metodo da Andrea

 void draw(const std::vector<geometry::vertex *>& vertices)
   { 
     l = vertices.size();
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_COLOR_MATERIAL);
     glEnable(GL_LIGHTING); //Enable lighting
     glEnable(GL_LIGHT0); //Enable light #0
     glEnable(GL_LIGHT1); //Enable light #1
     glEnable(GL_NORMALIZE); //Automatically normalize normals
     //glShadeModel(GL_SMOOTH); //Enable smooth shading

     //Add ambient light
     GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


     //Add positioned light
     GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
     GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
     glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
     glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

     //Add directed light
     GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
     //Coming from the direction (-1, 0.5, 0.5)
     GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
     glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
     glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

     glColor3f(1.0f, 1.0f, 0.0f);


     glBegin(GL_QUADS);
       //std::vector<geometry::vertex> vertices = test_load_vertex();
      // std::cout<<"Vertices size: "<<vertices.size()<<std::endl;

      glNewList(CARTESIO, GL_COMPILE);
         glColor3d(1.0, 1.0, 1.0);
         glBegin(GL_LINES);
            glVertex3f(-5.0f, 0.0f, 0.0f);
            glVertex3f(+5.0f, 0.0f, 0.0f);
      
         glEnd();
         glBegin(GL_LINES);
            glVertex3f(0.0f, -5.0f, 0.0f);
            glVertex3f(0.0f, +5.0f, 0.0f);
         glEnd();
      glEndList();

      //Disegna i poligoni
      glNewList(PANEL, GL_COMPILE);
         //glBegin(GL_LINE_LOOP);
         glBegin(GL_TRIANGLES);
            // glColor3f(1.0, 1.0, 1.0);
            float t = 0.5;
            float dt = 0.2; //(era 0.05)
            float color;
            
      
            for(geometry::vertex *v: vertices) {
               std::cout<<"x: "<<v->x<<"Y: "<<v->y<<"Z: "<<v->z<<std::endl;
               t+=dt;
               color = 0.5 + 0.3 * sin(t);
               glColor3f(color, color, color);
         glNormal3f(1.0f, 0.0f, 0.0f);
         glVertex3f(v->x, v->y, v->z);             
            }
      
    
            /*
            glColor3f(1.0, 0.0, 0.0);
            float t= 0.5;
            
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
            glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
            glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
            glColor3f(0.0, 1.0, 0.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
            glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
            glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
            glColor3f(0.0, 0.0, 1.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
            glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
            glVertex3f(vertices[8].x, vertices[8].y, vertices[8].z);
            glColor3f(1.0, 1.0, 0.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[9].x, vertices[9].y, vertices[9].z);
            glVertex3f(vertices[10].x, vertices[10].y, vertices[10].z);
            glVertex3f(vertices[11].x, vertices[11].y, vertices[11].z);
            glColor3f(1.0, 0.0, 0.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[12].x, vertices[12].y, vertices[12].z);
            glVertex3f(vertices[13].x, vertices[13].y, vertices[13].z);
            glVertex3f(vertices[14].x, vertices[14].y, vertices[14].z);
            glColor3f(0.0, 1.0, 0.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[15].x, vertices[15].y, vertices[15].z);
glVertex3f(vertices[16].x, vertices[16].y, vertices[16].z);
            glVertex3f(vertices[17].x, vertices[17].y, vertices[17].z);
            glColor3f(0.0, 0.0, 1.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[18].x, vertices[18].y, vertices[18].z);
            glVertex3f(vertices[19].x, vertices[19].y, vertices[19].z);
            glVertex3f(vertices[20].x, vertices[20].y, vertices[20].z);
            //glColor3f(1.0, 1.0, 0.0);
            t+=0.05; glColor3f(t, t, t);
            glVertex3f(vertices[21].x, vertices[21].y, vertices[21].z);
            glVertex3f(vertices[22].x, vertices[22].y, vertices[22].z);
            glVertex3f(vertices[23].x, vertices[23].y, vertices[23].z);
            */

            glColor3f(1.0, 1.0, 1.0);
         glEnd();
      glEndList(); 




   }

   void update(void)
   {

   
      static double t= 0.0;
      double dt=0.001,r=5.0,x,y;
      static double angle = 0.0;
      angle += 0.07;
      //Sleep(1000);
      dt=0.1;      
      t+=dt;
      x= r*cos(t); y= r*sin(t);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glCallList(CARTESIO);

    POINT cursorPos;
    GetCursorPos(&cursorPos);
    float xx = 0;
    xx = cursorPos.x;
    float yy = 0;
    yy = cursorPos.y;
      
    //Add positioned light
   /* GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = { 10.0f, -100.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    */


      //gluLookAt(10*sin(t), 10*cos(t), 0, 0, 0, 0, 0, 0, 1);
    
      glPushMatrix();  
      // setupCamera();
    
     //glRotatef(-yy*0.5f, 0.0f, 1.0f, 0.0f);
         glRotatef(xx*0.5f,0.0,0.0,-1.0);
         glTranslatef(0,-2.5,0);
         
    

     // glRotatef(angle, 0.0f, 1.0f, 0.0f);
     glColor3f(1.0f, 1.0f, 0.0f);
     glBegin(GL_QUADS);

    glEnd();
  
         //glTranslated(0,0,0);
         //glRotated(t*180/3.1415927,t*180/3.1415927,0,1);
         //Riempe i triangoli di colore


         glPolygonMode(  GL_FRONT_AND_BACK, GL_FILL);
         //Disegna semplicemente le linee ma non riempe i triangoli
         //glLineWidth(1.0);
         //glPolygonMode(  GL_FRONT_AND_BACK, GL_LINE);
         
         glCallList(PANEL);
      glPopMatrix();
   




   
   
      
   }