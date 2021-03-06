// generated by Fast Light User Interface Designer (fluid) version 1.0305

#include "PVCreativityUI.h"

void PVCreativityUI::cb_compute_i(Fl_Button*, void*) {
  int N = (int)this->N->value();
	int minutes = (int)this->minutes->value();
	double L = (double)this->L->value();
	double beta = (double)this->beta->value();
	double Z_S = (double)this->Z_S->value();
	double n_refraction_index = (double)this->n->value();
	double L_T = (double)this->L_T->value();
	double K = (double)this->K->value();
	double G_B = (double)this->G_B->value();



	double S = compute_absorbed_radiation_S(
		N,
		minutes,
		L,
		beta,
		Z_S,
		n_refraction_index,
		L_T,
		K,
		G_B,
		1);

	std::cout << "Da pressione di bottone" << std::endl
		<< "L: " << L << std::endl
		<< "beta: " << beta << std::endl
		<< "Z_S: " << Z_S << std::endl
		<< "L_T: " << L_T << std::endl
		<< "Refraction Index (n): " << n_refraction_index << std::endl
		<< "K: " << K << std::endl
		<< "Giorni (N): " << N << std::endl
		<< "Minuti (minutes): " << minutes << std::endl
		<< "G_B: " << G_B << std::endl
		<< "S: " << S << std::endl;
}
void PVCreativityUI::cb_compute(Fl_Button* o, void* v) {
  ((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_i(o,v);
}

PVCreativityUI::PVCreativityUI() {
  { window = new Fl_Double_Window(917, 1169, "Photovoltaic Creativity");
    window->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(640, 40, 230, 585, "Input Values");
      o->box(FL_THIN_UP_BOX);
      { L = new Fl_Value_Input(760, 60, 95, 23, "Latitude");
        L->maximum(360);
        L->value(35);
      } // Fl_Value_Input* L
      { beta = new Fl_Value_Input(760, 90, 95, 23, "Beta (Tilt)");
        beta->maximum(90);
        beta->value(30);
      } // Fl_Value_Input* beta
      { L_T = new Fl_Value_Input(760, 150, 95, 23, "Glass Thickness");
        L_T->value(0.002);
      } // Fl_Value_Input* L_T
      { G_B = new Fl_Value_Input(760, 300, 95, 23, "G_B");
        G_B->maximum(2000);
        G_B->value(715);
      } // Fl_Value_Input* G_B
      { compute = new Fl_Button(660, 590, 195, 20, "Compute");
        compute->callback((Fl_Callback*)cb_compute);
      } // Fl_Button* compute
      { N = new Fl_Value_Input(760, 240, 95, 23, "Day");
        N->minimum(1);
        N->maximum(365);
        N->value(1);
      } // Fl_Value_Input* N
      { minutes = new Fl_Value_Input(760, 270, 95, 23, "Minutes");
        minutes->minimum(-720);
        minutes->maximum(720);
      } // Fl_Value_Input* minutes
      { Z_S = new Fl_Value_Input(760, 120, 95, 23, "Z_S");
        Z_S->maximum(360);
      } // Fl_Value_Input* Z_S
      { n = new Fl_Value_Input(760, 180, 95, 23, "Refraction index");
        n->maximum(10);
        n->value(1.526);
      } // Fl_Value_Input* n
      { K = new Fl_Value_Input(760, 210, 95, 23, "K");
        K->maximum(100);
        K->value(4);
      } // Fl_Value_Input* K
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
