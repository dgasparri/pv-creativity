

#include <windows.h>
#include <FL/Fl.H>
#include "global.h"
/*#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#define _USE_MATH_DEFINES
#include <algorithm>
*/
// #include "fltk/PanelView.h"
#include "fltk/PVCreativityUI.h"


PVCreativityUI* fltk_window;


void idle_cb(void*)
{

	fltk_window->panel->redraw();
}


void init(std::vector<geometry::vertex*> vertices)
{
	fltk_window->panel->setVertices(vertices);
	Fl::add_idle(idle_cb, 0);
}



int main(int argc, char **argv) {

	fltk_window = new PVCreativityUI();
	fltk_window->show(1, argv);
	Fl::add_idle(idle_cb, 0);
	return(Fl::run());
}

