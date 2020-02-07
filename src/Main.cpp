#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#define _USE_MATH_DEFINES
#include <algorithm>

#include "fltk/PanelView.h"
#include "fltk/PVCreativityUI.h"
#include "lib/panel_io.h"
#include "lib/sun_fp.h"
#include "lib/sun_panel_fp.h"
#include "lib/geometry_fp.h"
using namespace std;


PanelView   *opengl_box;
// Fl_Text_Buffer* resultsBuffer;
PVCreativityUI* fltk_window;
// std::vector<geometry::vertex*> vertices;


void idle_cb(void*)
{

	opengl_box->redraw();
}


void init(std::vector<geometry::vertex*> vertices)
{
	opengl_box = fltk_window->panel;
	opengl_box->setVertices(vertices);

	//resultsBuffer = new Fl_Text_Buffer();
	//fltk_window->results->buffer(resultsBuffer);

	std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);

	Fl::add_idle(idle_cb, 0);
}


char** args = NULL;
int main(int argc, char **argv) {
	
	string nomeFile = "";
	args = argv;

	if (nomeFile == "" )
	{

	  // nomeFile = "./trianglesCirc2.csv";

		
	}

	//std::cout << " Nome: " << nomeFile;
    //vertices = panel_io::load_vertices(nomeFile);

	fltk_window = new PVCreativityUI();
	opengl_box = fltk_window->panel;
	//opengl_box->setVertices(vertices);

	//resultsBuffer = new Fl_Text_Buffer();
	//fltk_window->results->buffer(resultsBuffer);
	fltk_window->show(1, args);

	//std::vector<geometry::triangle> triangles;
	//triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	//for (int i = 0; i + 2 < vertices.size(); i += 3) {
	//	triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
	//	geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
	//}

	Fl::add_idle(idle_cb, 0);
	return(Fl::run());
}

