diff --git a/src/fltk/panel_opengl.cpp b/src/fltk/panel_opengl.cpp
index 01afbab..4877782 100644
--- a/src/fltk/panel_opengl.cpp
+++ b/src/fltk/panel_opengl.cpp
@@ -1,20 +1,97 @@
 #include "panel_opengl.h"
 #include "../lib/geometry_fp.h"
-#include <GL/glu.h> //per gluLookAt
+#include <C:\Users\andre\Desktop\C++\fltk-1.3.5\fltk-1.3.5\GL\glut.h>
+#include <FL/Fl.H>
+#include <FL/fl_message.H>
+using namespace std;
+
+
+#if defined(WIN32) || defined(__EMX__)
+#  define drand48() (((float) rand())/((float) RAND_MAX))
+#  define srand48(x) (srand((x)))
+#elif defined __APPLE__
+#  define drand48() (((float) rand())/((float) RAND_MAX))
+#  define srand48(x) (srand((x)))
+#endif
+
+//per gluLookAt
 
 
 namespace panel_opengl {
 
+	// Enable lighting
+	
+
+	void normalize(float* v)
+	{
+		float length =  sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
+
+		for (int i = 0; i < 3; i++)
+		{
+			v[i] = v[i] / length;
+		}
+	}
+
+	float* crossP(float* a, float* b)
+	{
+		float result[] = { a[1] * b[2] - a[2] * b[1], -(a[0] * b[2] - a[2] * b[0]), a[0] * b[1] - a[1] * b[0] };
+
+		normalize(result);
+
+		return result;
+	}
+	float* calcu_normal(float* a, float* b, float* c)
+	{
+		float x[] = {b[0]-a[0], b[1]-a[1], b[2]-a[2]};
+		float y[] = {c[0] - a[0], c[1] - a[1], c[2] - a[2] };
+
+		float* result = crossP(x, y);
+		return result;
+	}
+
+	int l = 0;
    void draw(const std::vector<geometry::vertex *>& vertices)
    { 
-      //std::vector<geometry::vertex> vertices = test_load_vertex();
-      std::cout<<"Vertices size: "<<vertices.size()<<std::endl;
+	   l = vertices.size();
+	   glEnable(GL_DEPTH_TEST);
+	   glEnable(GL_COLOR_MATERIAL);
+	   glEnable(GL_LIGHTING); //Enable lighting
+	   glEnable(GL_LIGHT0); //Enable light #0
+	   //glEnable(GL_LIGHT1); //Enable light #1
+	   glEnable(GL_NORMALIZE); //Automatically normalize normals
+	   //glShadeModel(GL_SMOOTH); //Enable smooth shading
+
+	   //Add ambient light
+	   GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
+	   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
+
+
+	   //Add positioned light
+	   GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
+	   GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
+	   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
+	   glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
+
+	   //Add directed light
+	   GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
+	   //Coming from the direction (-1, 0.5, 0.5)
+	   GLfloat lightPos1[] = { 0.5, 1, 1, 0.0f };
+	   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
+	   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
+
+	   glColor3f(1.0f, 1.0f, 0.0f);
+
+
+	   glBegin(GL_QUADS);
+       //std::vector<geometry::vertex> vertices = test_load_vertex();
+      // std::cout<<"Vertices size: "<<vertices.size()<<std::endl;
 
       glNewList(CARTESIO, GL_COMPILE);
          glColor3d(1.0, 1.0, 1.0);
          glBegin(GL_LINES);
             glVertex3f(-5.0f, 0.0f, 0.0f);
             glVertex3f(+5.0f, 0.0f, 0.0f);
+			
          glEnd();
          glBegin(GL_LINES);
             glVertex3f(0.0f, -5.0f, 0.0f);
@@ -37,9 +114,11 @@ namespace panel_opengl {
                t+=dt;
                color = 0.5 + 0.3 * sin(t);
                glColor3f(color, color, color);
-               glVertex3f(v->x, v->y, v->z);             
+			   glNormal3f(1.0f, 0.0f, 0.0f);
+			   glVertex3f(v->x, v->y, v->z);             
             }
 			
+		
             /*
             glColor3f(1.0, 0.0, 0.0);
             float t= 0.5;
@@ -96,28 +175,63 @@ namespace panel_opengl {
 
    void update(void)
    {
+
+	 
       static double t= 0.0;
       double dt=0.001,r=5.0,x,y;
       static double angle = 0.0;
-      angle += 0.1;
+      angle += 0.07;
       //Sleep(1000);
       dt=0.1;      
       t+=dt;
       x= r*cos(t); y= r*sin(t);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       glCallList(CARTESIO);
+
+	  POINT cursorPos;
+	  GetCursorPos(&cursorPos);
+	  float xx = 0;
+	  xx = cursorPos.x;
+	  float yy = 0;
+	  yy = cursorPos.y;
       
+	  //Add positioned light
+	 /* GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
+	  GLfloat lightPos0[] = { 10.0f, -100.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
+	  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
+	  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
+
+	  //Add directed light
+	  GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
+	  //Coming from the direction (-1, 0.5, 0.5)
+	  GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
+	  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
+	  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
+	  */
+
 
       //gluLookAt(10*sin(t), 10*cos(t), 0, 0, 0, 0, 0, 0, 1);
+	  
       glPushMatrix();  
+	    // setupCamera();
+	  
+		 //glRotatef(-yy*0.5f, 0.0f, 1.0f, 0.0f);
+         glRotatef(xx*0.5f,0.0,0.0,-1.0);
+         glTranslatef(0,-2.5,0);
          
-         glRotatef(angle,0.0,0.0,-1.0);
-         glTranslatef(-2.0,-2.5,0);
-         
-         
+		
+
+		 // glRotatef(angle, 0.0f, 1.0f, 0.0f);
+		 glColor3f(1.0f, 1.0f, 0.0f);
+		 glBegin(GL_QUADS);
+
+	glEnd();
+	
          //glTranslated(0,0,0);
          //glRotated(t*180/3.1415927,t*180/3.1415927,0,1);
          //Riempe i triangoli di colore
+
+
          glPolygonMode(	GL_FRONT_AND_BACK, GL_FILL);
          //Disegna semplicemente le linee ma non riempe i triangoli
          //glLineWidth(1.0);
@@ -125,6 +239,13 @@ namespace panel_opengl {
          
          glCallList(PANEL);
       glPopMatrix();
+	 
+
+
+
+
+	 
+	 
       
    }
 
