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
Fl_Text_Buffer* resultsBuffer;
PVCreativityUI* fltk_window;



void idle_cb(void*)
{

	opengl_box->redraw();
}

void init(std::vector<geometry::vertex*> vertices)
{
	//fltk_window = new PVCreativityUI();
	opengl_box = fltk_window->panel;
	opengl_box->setVertices(vertices);

	resultsBuffer = new Fl_Text_Buffer();
	fltk_window->results->buffer(resultsBuffer);
	//fltk_window->show(1, args);

	std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	for (int i = 0; i + 2 < vertices.size(); i += 3) {
		triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
		geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
	}


	double S[365];
	for (int N = 1; N <= 365; N++)
		for (int h = 0; h < 9; h++)
			S[N - 1] = 0;



	Fl::add_idle(idle_cb, 0);
	//Fl::run();
}


char** args = NULL;
int main(int argc, char **argv) {
	std::vector<geometry::vertex*> vertices;
	string nomeFile = "";
	args = argv;

	if (nomeFile == "" )
	{

	   nomeFile = "./trianglesCirc2.csv";

		
	}
	//const std::vector<geometry::vertex*> vertices = panel_io::test_vertices_2();

	std::cout << " Nome: " << nomeFile;
	//std::cout << " Nome2: " << "C:/Users/andre/source/repos/Progetto/geometries/trianglesCirc2.csv";
    vertices = panel_io::load_vertices(nomeFile);
	//const std::vector<geometry::vertex*> vertices = panel_io::load_vertices("C:/Users/andre/source/repos/Progetto/geometries/trianglesSinu.csv");

	fltk_window = new PVCreativityUI();
	opengl_box = fltk_window->panel;
	opengl_box->setVertices(vertices);

	resultsBuffer = new Fl_Text_Buffer();
	fltk_window->results->buffer(resultsBuffer);
	fltk_window->show(1, args);

	std::vector<geometry::triangle> triangles;
	triangles.reserve(vertices.size() / 3 + 1);
	//Checks for 3 available vertices
	for (int i = 0; i + 2 < vertices.size(); i += 3) {
		triangles.emplace_back(geometry::triangle(*vertices[i], *vertices[i + 1], *vertices[i + 2]));
		geometry::plane pl = geometry::fplane(*vertices[i], *vertices[i + 1], *vertices[i + 2]);
	}

	//double S[365][9];
	double S[365];
	for (int N = 1; N <= 365; N++)
		for (int h = 0; h < 9; h++)
			S[N - 1] = 0;

	Fl::add_idle(idle_cb, 0);
	Fl::run();
	return 1;
}

