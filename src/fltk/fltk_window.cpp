#define _CRT_NONSTDC_NO_DEPRECATE
#include <windows.h>
#include <FL/Fl.H>
#include "fltk_window.h"

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <Fl/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>

#include "../global.h"



#include "fltk_3dpanel.h"


#include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
#include "../lib/geometry_fp.h"
#include "../../pv-creativity/gnuplot.h"
#include "../lib/panel_irradiance.h"
#include "fltk_actions.h"





void fltk_window_t::cb_compute(Fl_Button* o, void* v) 
{
	fltk_actions::calcola(
		  fltk_window->L->value(), //Lat degrees
		  fltk_window->K_->value(), 
		  fltk_window->n->value(), //Refraction index
		  fltk_window->thickness_L->value(), 
		  fltk_window->buff);
  //((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_i(o,v);
}
void fltk_window_t::cb_plot(Fl_Button* o, void* v) {
	fltk_actions::PlotIT();
	//((PVCreativityUI*)(o->parent()->parent()->user_data()))->cb_compute_plot(o, v);
}

 
fltk_window_t::fltk_window_t() {
  { 
		//double taualpha_n, double M, double G_B, double R_B, double K_theta_B

		window = new Fl_Double_Window(1024, 800, "Photovoltaic Creativity");
        window->user_data((void*)(this));
       {
			Fl_Group* o = new Fl_Group(640, 40, 230, 585, "Input Values");
            o->box(FL_THIN_UP_BOX);
	        { 
			  openfile = new Fl_Button(660, 50, 195, 20, "Segli File");
			  openfile->callback((Fl_Callback*)fltk_actions::open_input_file);

			} // Fl_Value_Input* beta
			{ 
			  compute = new Fl_Button(660, 590, 195, 20, "Compute");
			  compute->callback((Fl_Callback*)fltk_window_t::cb_compute);
			}
			{
				compute = new Fl_Button(660, 550, 195, 20, "Plot It");
				compute->callback((Fl_Callback*)fltk_window_t::cb_plot);
			}
			{ 
				thickness_L = new Fl_Value_Input(760, 150, 95, 23, "Glass Thickness");
				thickness_L->value(global::thickness_L);
				
			}
			{ 
				K_ = new Fl_Value_Input(760, 210, 95, 23, "K");
				K_->maximum(100);
				K_->value(global::K);
				
			} 
			{ 
				n = new Fl_Value_Input(760, 180, 95, 23, "Refraction index");
				n->maximum(10);
				n->value(global::n_refraction_index);
				
			}
			{
				L = new Fl_Value_Input(760, 240, 95, 23, "Latitude");
				L->value(global::UniBo_Lat_deg);

			}

 
			o->end();
		 } // Fl_Group* o
		{
			
		   panel = new fltk_3dpanel(25, 25, 600, 600, "pframe");
      
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

void fltk_window_t::show(int argc, char **argv) {
  this->window->show(argc,argv);
  // nomeFile = "C:/Users/andre/source/repos/Progetto/geometries/trianglesCirc2.csv";
  // panel->vertices = panel_io::load_vertices(nomeFile);
}
