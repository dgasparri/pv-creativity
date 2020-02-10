

#include <windows.h>
#include <FL/Fl.H>
#include "global.h"
/*#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#define _USE_MATH_DEFINES
#include <algorithm>
*/
// #include "fltk/PanelView.h"
#include "fltk/fltk_window.h"


fltk_window_t* fltk_window;


void idle_cb(void*)
{

	fltk_window->panel->redraw();
}

/*
//IF IT WORKS, IT SHOULB BE ERASED - NOT CALLED ANYMORE
//MAYBE IT MISSES THE Fl::add_idle
void init(std::vector<geometry::vertex*> vertices)
{
	fltk_window->panel->set_vertices(vertices);
	Fl::add_idle(idle_cb, 0);
}
*/


int main(int argc, char **argv) {

	fltk_window = new fltk_window_t();
	fltk_window->show(1, argv);
	Fl::add_idle(idle_cb, 0);
	return(Fl::run());
}

