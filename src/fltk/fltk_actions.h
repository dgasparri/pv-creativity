#include <FL/Fl_File_Chooser.H>

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "../lib/geometry_fp.h"

namespace fltk_actions {
    void assign_file(Fl_File_Chooser* w, void* userdata);
    void open_input_file();
    void calcola(double n_refraction_index, double thickness, double K, Fl_Text_Buffer* buff, Fl_Value_Input* L_T, Fl_Value_Input* K_, Fl_Value_Input* n, Fl_Value_Input* L);
    void PlotIT();
}
