#pragma once

#include <FL/Fl_Gl_Window.H>
#include <windows.h>
#include <FL/gl.h>
#include <GL/glu.h>
#include <functional>
#include "vector"
#include "../lib/geometry_fp.h"
#include "fltk_3dpanel_opengl.h"



class fltk_3dpanel : public Fl_Gl_Window {
	void draw();
	std::vector<geometry::vertex *> vertices;
	std::vector<geometry::triangle *> triangles;


public:

	fltk_3dpanel(int x, int y, int w, int h, const char* l = 0);
	void set_vertices(const std::vector<geometry::vertex *>& vertices);
	std::vector<geometry::vertex *>& get_vertices();
	std::vector<geometry::triangle *>& get_triangles();
};



