#pragma once
#ifndef PANELVIEW_HPP
#define PANELVIEW_HPP

#include <FL/Fl_Gl_Window.H>

class PanelView : public Fl_Gl_Window {
	void draw();
public:
	PanelView(int x, int y, int w, int h, const char* l = 0) : Fl_Gl_Window(x, y, w, h, l) {}
};


#endif // PANEL_HPP

