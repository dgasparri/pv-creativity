#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Windows.h>
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include "fltk_3dpanel.h"

// extern int  arg;
// extern char** args; 


class fltk_window_t {

public:
  fltk_window_t();
protected:
  Fl_Double_Window *window;
public:
  Fl_Value_Input *L;
  Fl_Value_Input *n;
  Fl_Value_Input *thickness_L;
  Fl_Value_Input *K_;

  // Fl_Value_Input *beta;
  // Fl_Value_Input *G_B;
 
protected:
  Fl_Button *compute;
  Fl_Button *openfile;
private:
  static void cb_compute(Fl_Button*, void*);
  static void cb_plot(Fl_Button*, void*);
public:
  // Fl_Value_Input *N;
  // Fl_Value_Input *minutes;
  //Fl_Value_Input *Z_S;


  fltk_3dpanel *panel;
  Fl_Text_Display *results;
  Fl_Text_Buffer* buff;
  void show(int argc, char **argv);
};

extern fltk_window_t* fltk_window;