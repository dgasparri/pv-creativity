#include <windows.h>
#include <FL/Fl.H>
#include "form.h"
#include "frame.h"
#include "pv_output.h"

extern Frame   *scene;

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();    
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	compute_absorbed_radiation_S();
	
	make_window();
	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 0;
}
//-------------------------------------------------------------------------------------------------
