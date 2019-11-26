#pragma once

#include <FL/Fl_Gl_Window.H>
#include <windows.h>
#include <FL/gl.h>
#include <GL/glu.h>
#include <functional>
#include "../lib/geometry_fp.h"
#include "panel_opengl.h"



class PanelView : public Fl_Gl_Window {
	void draw();
	std::vector<geometry::vertex *> vertices;
public:

	PanelView(int x, int y, int w, int h, const char* l = 0);
	void setVertices(const std::vector<geometry::vertex *>& vertices);
};



