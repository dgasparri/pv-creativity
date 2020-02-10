#pragma once
#include <windows.h>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "fltk_window.h"
#include "../lib/panel_io.h"
#include "../lib/geometry_fp.h"
#include "../lib/sun_fp.h"
#include "../lib/panel_irradiance.h"
#include "fltk_3dpanel_opengl.h"

#include "../../pv-creativity/gnuplot.h"

extern fltk_window_t* fltk_window;

namespace fltk_actions {
    void assign_file(Fl_File_Chooser* w, void* userdata);
    void open_input_file();
    void run_simulation(double l_L_deg,	double K, 	double n_refraction_index, 	double thickness, Fl_Text_Buffer* buff);
    void plot_yearly();
    void plot_daily(double day);
}
