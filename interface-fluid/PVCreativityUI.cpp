// generated by Fast Light User Interface Designer (fluid) version 1.0305

#include "PVCreativityUI.h"

void PVCreativityUI::cb_compute_i(Fl_Button*, void*) {
  compute_absorbed_radiation_S(this->L, this->beta, this->delta, this->G_B);
}
void PVCreativityUI::cb_compute(Fl_Button* o, void* v) {
  ((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_i(o,v);
}

PVCreativityUI::PVCreativityUI() {
  { window = new Fl_Double_Window(917, 1169, "Photovoltaic Creativity");
    window->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(670, 40, 200, 600, "Input Values");
      o->box(FL_THIN_UP_BOX);
      { L = new Fl_Value_Input(760, 60, 95, 23, "Latitude");
        L->maximum(360);
        L->value(35);
      } // Fl_Value_Input* L
      { beta = new Fl_Value_Input(760, 90, 95, 23, "Beta (Tilt)");
        beta->maximum(90);
        beta->value(30);
      } // Fl_Value_Input* beta
      { delta = new Fl_Value_Input(760, 120, 95, 23, "delta");
        delta->maximum(90);
        delta->value(23.09);
      } // Fl_Value_Input* delta
      { G_B = new Fl_Value_Input(760, 150, 95, 23, "G_B");
        G_B->maximum(2000);
        G_B->value(715);
      } // Fl_Value_Input* G_B
      { compute = new Fl_Button(685, 590, 170, 35, "Compute");
        compute->callback((Fl_Callback*)cb_compute);
      } // Fl_Button* compute
      o->end();
    } // Fl_Group* o
    { panel = new PanelView(25, 25, 600, 600, "pframe");
      panel->box(FL_EMBOSSED_BOX);
      panel->color(FL_BACKGROUND_COLOR);
      panel->selection_color(FL_BACKGROUND_COLOR);
      panel->labeltype(FL_NORMAL_LABEL);
      panel->labelfont(0);
      panel->labelsize(14);
      panel->labelcolor(FL_FOREGROUND_COLOR);
      panel->align(Fl_Align(FL_ALIGN_CENTER));
      panel->when(FL_WHEN_RELEASE);
    } // PanelView* panel
    { results = new Fl_Text_Display(25, 645, 600, 400, "Results");
    } // Fl_Text_Display* results
    window->end();
  } // Fl_Double_Window* window
}

void PVCreativityUI::show(int argc, char **argv) {
  this->window->show(argc,argv);
}
