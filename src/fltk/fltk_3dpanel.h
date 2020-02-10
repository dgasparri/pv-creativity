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
	std::vector<geometry::vertex *> *vertices = nullptr;
	std::vector<geometry::triangle *> *triangles = nullptr;


public:

	fltk_3dpanel(int x, int y, int w, int h, const char* l = 0);
	void clear_vertices();
	void clear_triangles();
	void set_vertices(std::vector<geometry::vertex *> *v);
	void set_triangles(std::vector<geometry::triangle *> *t);
	std::vector<geometry::vertex *> &get_vertices();
	std::vector<geometry::triangle *> &get_triangles();
	std::vector<geometry::vertex *> *get_vertices_ptr();
	std::vector<geometry::triangle *> *get_triangles_ptr();

};



