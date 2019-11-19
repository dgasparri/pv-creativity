// generated by Fast Light User Interface Designer (fluid) version 1.0305

#ifndef PVCreativityUI_h
#define PVCreativityUI_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Windows.h>
#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include "PanelView.h"
#include <FL/Fl_Text_Display.H>

class PVCreativityUI {
public:
  PVCreativityUI();
protected:
  Fl_Double_Window *window;
public:
  Fl_Value_Input *L;
  Fl_Value_Input *beta;
  Fl_Value_Input *L_T;
  Fl_Value_Input *G_B;
protected:
  Fl_Button *compute;
private:
  inline void cb_compute_i(Fl_Button*, void*);
  static void cb_compute(Fl_Button*, void*);
public:
  Fl_Value_Input *N;
  Fl_Value_Input *minutes;
  Fl_Value_Input *Z_S;
  Fl_Value_Input *n;
  Fl_Value_Input *K;
  PanelView *panel;
  Fl_Text_Display *results;
  void show(int argc, char **argv);
};
#endif
