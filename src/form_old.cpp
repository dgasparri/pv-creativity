#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

#include "Frame.h"
#include "form.h"

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600


Frame        *scene;

//-------------------------------------------------------------------------------------------------
void CreateMyWindow(void) {
  int w_est,h_est;
  
  w_est= 23+SCREEN_WIDTH+200+23;   h_est= 23+SCREEN_HEIGHT+200+23;
  Fl_Window *form;     
  form=   new Fl_Window(w_est,h_est,"TEsT");
          new Fl_Box(FL_DOWN_FRAME,20,20,SCREEN_WIDTH+6,SCREEN_HEIGHT+6,"");
  scene=  new Frame(23,23,SCREEN_WIDTH,SCREEN_HEIGHT, 0);
  //form->resizable(scene);
  scene->end();

  Fl_Group *rightpanel = new Fl_Group(SCREEN_WIDTH + 23, 10, 200, 200, "Parameters");
  rightpanel->box(FL_ENGRAVED_BOX); 
  rightpanel->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP); 
  rightpanel->labelsize(24);
  new Fl_Input(170 + 10, 30 + 00, 200, 20, "G_B:");
  new Fl_Input(170 + 10, 30 + 30, 200, 20, "Delta:");
  new Fl_Input(170 + 10, 30 + 60, 200, 20, "L:");
  new Fl_Input(170 + 10, 30 + 90, 200, 20, "K:");
  rightpanel->end();


  form->end();
  form->show();
  scene->show();
  rightpanel->show();
}
//-------------------------------------------------------------------------------------------------


