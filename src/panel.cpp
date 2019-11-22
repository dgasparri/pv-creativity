#include "panel.h"
#include <iostream>
#include <GL/glu.h> //per gluLookAt

std::vector<p_geometry::vertex> temp_vertices();
std::vector<p_geometry::vertex> test_load_vertex();

namespace panel {

   void draw(void)
   {
      std::vector<p_geometry::vertex> vertices = test_load_vertex();
      std::cout<<"Vertices size: "<<vertices.size()<<std::endl;
      /*
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
      */

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
            /*
            for(p_geometry::vertex v: vertices) {
               std::cout<<"x: "<<v.x<<"Y: "<<v.y<<"Z: "<<v.z<<std::endl;
               glVertex3f(v.x, v.y, v.z);             
            }
            */
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
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(vertices[12].x, vertices[12].y, vertices[12].z);
            glVertex3f(vertices[13].x, vertices[13].y, vertices[13].z);
            glVertex3f(vertices[14].x, vertices[14].y, vertices[14].z);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(vertices[15].x, vertices[15].y, vertices[15].z);
            glVertex3f(vertices[16].x, vertices[16].y, vertices[16].z);
            glVertex3f(vertices[17].x, vertices[17].y, vertices[17].z);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(vertices[18].x, vertices[18].y, vertices[18].z);
            glVertex3f(vertices[19].x, vertices[19].y, vertices[19].z);
            glVertex3f(vertices[20].x, vertices[20].y, vertices[20].z);
            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(vertices[21].x, vertices[21].y, vertices[21].z);
            glVertex3f(vertices[22].x, vertices[22].y, vertices[22].z);
            glVertex3f(vertices[23].x, vertices[23].y, vertices[23].z);


            glColor3f(1.0, 1.0, 1.0);
         glEnd();
      glEndList(); 




   }

   void update(void)
   {
      static double t= 0.0;
      double dt=0.001,r=2.0,x,y;
      Sleep(1000);      
      t+=dt;
      x= r*cos(t); y= r*sin(t);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glCallList(CARTESIO);
      

      //gluLookAt(10*sin(t), 10*cos(t), 0, 0, 0, 0, 0, 0, 1);
      glPushMatrix();  
         //glTranslated(x,y,0);
         //glRotated(t*180/3.1415927,t*180/3.1415927,0,1);
         //Riempe i triangoli di colore
         glPolygonMode(	GL_FRONT_AND_BACK, GL_FILL);
         //Disegna semplicemente le linee ma non riempe i triangoli
         //glLineWidth(1.0);
         //glPolygonMode(	GL_FRONT_AND_BACK, GL_LINE);
         
         glCallList(PANEL);
      glPopMatrix();
      
   }



}
