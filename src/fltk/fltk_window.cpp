#define _CRT_NONSTDC_NO_DEPRECATE
#include <windows.h>
#include <FL/Fl.H>
#include "fltk_window.h"
#include "fltk_3dpanel.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
#include "../lib/geometry_fp.h"
#include "../../pv-creativity/gnuplot.h"
#include "../lib/panel_irradiance.h"
#include "fltk_actions.h"

using namespace std;

std::string nf = "";
double refraction_holder = 1.526;
double thickness_holder  = 0.002;
double K_holder          = 4;
double L_rad             = 44 / 180 * M_PI;



Fl_Value_Input* L_T;
Fl_Value_Input* K_;
Fl_Value_Input* n;
Fl_Value_Input* L;

std::vector<geometry::vertex*> vertices;
std::string nomeFile;

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
void PVCreativityUI::cb_compute(Fl_Button* o, void* v) {
  
  calcola(refraction_holder, thickness_holder, K_holder, buff, L_T, K_, n, L);
  //((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_i(o,v);
}
void PVCreativityUI::cb_computePlot(Fl_Button* o, void* v) {
	PlotIT();
	//((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_plot(o, v);
}

 
PVCreativityUI::PVCreativityUI() {
  { 
		//double taualpha_n, double M, double G_B, double R_B, double K_theta_B

		window = new Fl_Double_Window(1024, 800, "Photovoltaic Creativity");
        window->user_data((void*)(this));
       {
			Fl_Group* o = new Fl_Group(640, 40, 230, 585, "Input Values");
            o->box(FL_THIN_UP_BOX);
	        { 
			  openfile = new Fl_Button(660, 50, 195, 20, "Segli File");
			  openfile->callback((Fl_Callback*)open_input_file);

			} // Fl_Value_Input* beta
			{ 
			  compute = new Fl_Button(660, 590, 195, 20, "Compute");
			  compute->callback((Fl_Callback*)cb_compute);
			}
			{
				compute = new Fl_Button(660, 550, 195, 20, "Plot It");
				compute->callback((Fl_Callback*)cb_computePlot);
			}
			{ 
				L_T = new Fl_Value_Input(760, 150, 95, 23, "Glass Thickness");
				L_T->value(0.002);
				
			}
			{ 
				K_ = new Fl_Value_Input(760, 210, 95, 23, "Fattore Kappa (K)");
				K_->maximum(100);
				K_->value(4);
				
			} 
			{ 
				n = new Fl_Value_Input(760, 180, 95, 23, "Refraction index");
				n->maximum(10);
				n->value(1.526);
				
			}
			{
				L = new Fl_Value_Input(760, 240, 95, 23, "Latitude");
				double lat = (44 / 180 * M_PI);
				L->value(lat);

			}

 
			o->end();
		 } // Fl_Group* o
		{
			
		   panel = new PanelView(25, 25, 600, 600, "pframe");
      
		 } // PanelView* panel
		 {
			
		
			buff = new Fl_Text_Buffer();
			results = new Fl_Text_Display(25, 645, 600, 150, "Results");
			results->textcolor(FL_BLACK);
			results->buffer(buff);
			window->resizable(results);
		 } 
		window->end();
  } 
}

void PVCreativityUI::show(int argc, char **argv) {
  this->window->show(argc,argv);
  nomeFile = "C:/Users/andre/source/repos/Progetto/geometries/trianglesCirc2.csv";
  vertices = panel_io::load_vertices(nomeFile);
}
