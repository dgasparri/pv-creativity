#include "fltk_3dpanel_opengl.h"
#include "../lib/geometry_fp.h"
#include <GL/glut.h>
#include <FL/Fl.H>
#include <FL/fl_message.H>
using namespace std;


#if defined(WIN32) || defined(__EMX__)
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#elif defined __APPLE__
#  define drand48() (((float) rand())/((float) RAND_MAX))
#  define srand48(x) (srand((x)))
#endif

//per gluLookAt




// Enable lighting


void fltk_3dpanel_opengl::normalize(float* v)
{
   float length =  sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

   for (int i = 0; i < 3; i++)
   {
      v[i] = v[i] / length;
   }
}

float* fltk_3dpanel_opengl::crossP(float* a, float* b)
{
   float result[] = { a[1] * b[2] - a[2] * b[1], -(a[0] * b[2] - a[2] * b[0]), a[0] * b[1] - a[1] * b[0] };

   fltk_3dpanel_opengl::normalize(result);

   return result;
}
float* fltk_3dpanel_opengl::calcu_normal(float* a, float* b, float* c)
{
   float x[] = {b[0]-a[0], b[1]-a[1], b[2]-a[2]};
   float y[] = {c[0] - a[0], c[1] - a[1], c[2] - a[2] };

   float* result = fltk_3dpanel_opengl::crossP(x, y);
   return result;
}

void fltk_3dpanel_opengl::draw(std::vector<geometry::vertex *> *vertices)
{ 
   int l = vertices->size(); // 8.2.2020 was global
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING); //Enable lighting
   glEnable(GL_LIGHT0); //Enable light #0
   //glEnable(GL_LIGHT1); //Enable light #1
   glEnable(GL_NORMALIZE); //Automatically normalize normals
   glShadeModel(GL_SMOOTH); //Enable smooth shading

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
   GLfloat lightPos1[] = { 0.5, 1, 1, 0.0f };
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

   glColor3f(1.0f, 1.0f, 0.0f);


   glNewList(CARTESIO, GL_COMPILE);
      glColor3d(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
         glVertex3f(-5.0f, 0.0f, 0.0f);
         glVertex3f(+5.0f, 0.0f, 0.0f);
      
      glEnd();
      glBegin(GL_LINES);
         glVertex3f(0.0f, 0.0f, -5.0f);
         glVertex3f(0.0f, 0.0f, +5.0f);
      glEnd();
   glEndList();

   //Disegna i poligoni
   glNewList(PANEL, GL_COMPILE);
      glBegin(GL_TRIANGLES);
         // Colors da RGB
         // glColor3f(16.0/255.0, 28.0/255.0, 133.0/255.0);
         // glColor3f(1.0, 1.0, 1.0);
         const float baseRed = 16.0/255.0;
         const float baseGreen = 28.0/255.0;
         const float baseBlue = 133.0/255.0;
         float t = 0.05;
         float dt = 0.05;
         // cambiato il 7.2.2020, prima era:
         // float t = 0.5;
         // float dt = 0.2; //(era 0.05)
         float colorRed, colorGreen, colorBlue;
         
      
         for(geometry::vertex *v: (*vertices)) {
            std::cout<<"x--: "<<v->x<<"Y: "<<v->y<<"Z: "<<v->z<<std::endl;
            t+=dt;
            colorRed = baseRed + 0.3 * sin(t);
            colorGreen = baseGreen + 0.3 * sin(t);
            colorBlue = baseBlue + 0.3 * sin(t);
            glColor3f(colorRed, colorGreen, colorBlue);
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(v->x, v->y, v->z);             
         }
      
   
      glEnd();
   glEndList(); 




}

void fltk_3dpanel_opengl::update(void)
{

   
   static double t= 0.0;
   double dt=0.001,r=5.0,x,y;
   static double angle = 0.0;
   angle += 0.05;
   //Cambiato 7.2.2020, prima era:
   // angle += 0.07;
   //Sleep(1000);
   dt=0.001; 
   // cambiato 7.2.2020, prima era:
   // dt=0.1;      
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
   //Tolto commento il 7.2.2020
   GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
   GLfloat lightPos0[] = { 10.0f, -100.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

   //Add directed light
   GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
   //Coming from the direction (-1, 0.5, 0.5)
   GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);



   //gluLookAt(10*sin(t), 10*cos(t), 0, 0, 0, 0, 0, 0, 1);
   
   glPushMatrix();  
      // setupCamera();
   
      //glRotatef(-yy*0.5f, 0.0f, 1.0f, 0.0f);
      glRotatef(xx*0.5f,0.0,0.0,-1.0);
      // Commentato il 7.2.2020
      // glTranslatef(0,-2.5,0);
      
   

      // glRotatef(angle, 0.0f, 1.0f, 0.0f);
      glColor3f(1.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);

glEnd();

      // Tolto il commento il 7.2.2020
      glTranslated(0,0,0);
      //glRotated(t*180/3.1415927,t*180/3.1415927,0,1);
      //Riempe i triangoli di colore


      // Commentato il 7.2.2020
      // glPolygonMode(	GL_FRONT_AND_BACK, GL_FILL);
      //Disegna semplicemente le linee ma non riempe i triangoli
      //glLineWidth(1.0);
      //glPolygonMode(	GL_FRONT_AND_BACK, GL_LINE);
      
      glCallList(PANEL);
   glPopMatrix();
   
 
   
   
}



