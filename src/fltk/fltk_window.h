#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#include "../global.h"
#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <iostream>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include "fltk_3dpanel.h"
#include "fltk_actions.h"



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
  Fl_Value_Input *day_to_plot;

 
protected:
  Fl_Button *run_simulation,*plot_year, *plot_day;
  Fl_Button *openfile;
private:
  static void cb_run_simulation(Fl_Button*, void*);
  static void cb_plot_year(Fl_Button*, void*);
  static void cb_plot_day(Fl_Button*, void*);
public:

  fltk_3dpanel *panel;
  Fl_Text_Display *results;
  Fl_Text_Buffer* buff;
  void show(int argc, char **argv);
};

extern fltk_window_t* fltk_window;