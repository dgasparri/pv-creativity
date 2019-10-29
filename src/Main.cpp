#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "form.h"
#include "frame.h"
#include "pv_output.h"

Frame   *scene;

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();    
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	compute_absorbed_radiation_S();
	
	Fl_Double_Window* w = make_window();
	scene = new Frame(23, 23, 600, 600, 0); 
	w->end();
	w->show();
	scene->show();

	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 0;
}
//-------------------------------------------------------------------------------------------------
