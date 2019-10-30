#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
// #include "form.h"

// #include "frame.h"
#include "PanelView.h"
#include "pv_output.h"
#include "PVCreativityUI.h"

PanelView   *scene;
Fl_Text_Buffer* resultsBuffer;

//-------------------------------------------------------------------------------------------------
void idle_cb(void*)
{
  scene->redraw();    
}
//-------------------------------------------------------------------------------------------------
int main(int argc, char **argv) {
	// compute_absorbed_radiation_S();
	

	PVCreativityUI* w = new PVCreativityUI();
	scene = w->panel;
	
	resultsBuffer = new Fl_Text_Buffer();
	w->results->buffer(resultsBuffer);

	w->show(argc, argv);

	/*
	resultsBuffer->text("line 0\nline 1\nline 2\n"
		"line 3\nline 4\nline 5\n"
		"line 6\nline 7\nline 8\n"
		"line 9\nline 10\nline 11\n"
		"line 12\nline 13\nline 14\n"
		"line 15\nline 16\nline 17\n"
		"line 18\nline 19\nline 20\n"
		"line 21\nline 22\nline 23\n");
		*/
	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 0;
}
//-------------------------------------------------------------------------------------------------
