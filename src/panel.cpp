#include "panel.h"

namespace panel {

   void draw(void)
   {
      std::vector<p_geometry::vertex> vertices;
      vertices.emplace_back(p_geometry::vertex(-3.0, -3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 3.0, -3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));
   
      vertices.emplace_back(p_geometry::vertex(-3.0, -3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex(-3.0,  3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));
   
      vertices.emplace_back(p_geometry::vertex( 3.0,  3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex(-3.0,  3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));
      
      vertices.emplace_back(p_geometry::vertex( 3.0,  3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 3.0, -3.0, 0.0));
      vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));


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
         glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);
            //for(p_geometry::vertex v: vertices) {
            //   std::cout<<"x: "<<v.x<<"Y: "<<v.y<<"Z: "<<v.z<<std::endl;
            //   glVertex3f(v.x, v.y, v.z);             
            //}
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
            glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
            glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
            glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
            glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
            glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
            glVertex3f(vertices[8].x, vertices[8].y, vertices[8].z);
            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(vertices[9].x, vertices[9].y, vertices[9].z);
            glVertex3f(vertices[10].x, vertices[10].y, vertices[10].z);
            glVertex3f(vertices[11].x, vertices[11].y, vertices[11].z);

            glColor3f(1.0, 1.0, 1.0);
         glEnd();
      glEndList(); 




   }

   void update(void)
   {
      static double t= 0.0;
      double dt=0.001,r=2.0,x,y;
      
      t+=dt;
      x= r*cos(t); y= r*sin(t);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glCallList(CARTESIO);
      
      glPushMatrix();  
         glTranslated(x,y,0);
         glRotated(t*180/3.1415927,t*180/3.1415927,0,1);
         //Riempe i triangoli di colore
         glPolygonMode(	GL_FRONT_AND_BACK, GL_FILL);
         //Disegna semplicemente le linee ma non riempe i triangoli
         //glLineWidth(1.0);
         //glPolygonMode(	GL_FRONT_AND_BACK, GL_LINE);
         
         glCallList(PANEL);
      glPopMatrix();
      
   }



}
