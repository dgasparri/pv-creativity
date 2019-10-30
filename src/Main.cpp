#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
// #include "form.h"

// #include "frame.h"
#include "PanelView.h"
#include "pv_output.h"
#include "PVCreativityUI.h"

PanelView   *scene;

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();    
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	compute_absorbed_radiation_S();
	
	// Fl_Double_Window* w = make_window();
	/* scene = new PanelView(23, 23, 600, 600, 0); 
	w->end();
	w->show();
	scene->show();
	*/

	PVCreativityUI* w = new PVCreativityUI();
	scene = w->panel;
	//w->show();

	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 0;
}
//-------------------------------------------------------------------------------------------------
