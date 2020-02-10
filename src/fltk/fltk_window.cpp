
#include "fltk_window.h"

#include "fltk_actions.h"//Must stay here to avoid loop referencing


void fltk_window_t::cb_run_simulation(Fl_Button* o, void* v) 
{
	fltk_actions::run_simulation(
		  fltk_window->L->value(), //Lat degrees
		  fltk_window->K_->value(), 
		  fltk_window->n->value(), //Refraction index
		  fltk_window->thickness_L->value(), 
		  fltk_window->buff);
}
void fltk_window_t::cb_plot_year(Fl_Button* o, void* v) {
	fltk_actions::plot_yearly();
}

void fltk_window_t::cb_plot_day(Fl_Button* o, void* v) {

	fltk_actions::plot_daily(fltk_window->day_to_plot->value());
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
			  openfile = new Fl_Button(660, 50, 195, 20, "Open File");
			  openfile->callback((Fl_Callback*)fltk_actions::open_input_file);

			} // Fl_Value_Input* beta
			{ 
			  run_simulation = new Fl_Button(660, 510, 195, 20, "Run Simulation");
			  run_simulation->callback((Fl_Callback*)fltk_window_t::cb_run_simulation);
			}
			{
				plot_year = new Fl_Button(660, 550, 195, 20, "Plot Yearly Data");
				plot_year->callback((Fl_Callback*)fltk_window_t::cb_plot_year);
			}
			{ 
				day_to_plot = new Fl_Value_Input(660, 590, 30, 20);
				day_to_plot->value(180);
				
			}
			{
				plot_day = new Fl_Button(700, 590, 155, 20, "Plot Day");
				plot_day->callback((Fl_Callback*)fltk_window_t::cb_plot_day);
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
}
