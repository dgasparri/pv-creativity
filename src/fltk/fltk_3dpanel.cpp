#include "PanelView.h"
#include "../lib/panel_io.h"


PanelView::PanelView(int x, int y, int w, int h, const char* l) 
	: Fl_Gl_Window(x, y, w, h, l) {
		box(FL_EMBOSSED_BOX);
    	color(FL_BACKGROUND_COLOR);
    	selection_color(FL_BACKGROUND_COLOR);
    	labeltype(FL_NORMAL_LABEL);
    	labelfont(0);
    	labelsize(14);
    	labelcolor(FL_FOREGROUND_COLOR);
    	align(Fl_Align(FL_ALIGN_CENTER));
    	when(FL_WHEN_RELEASE);
}


void PanelView::setVertices(const std::vector<geometry::vertex *>& v) {
	std::cout << "Numero vertici: " << v.size() << std::endl;
	vertices = v;
}






void PanelView::draw() {
	if (!valid()) {

		glClearColor(0.0, 0.0, 0.0, 1);                        // Turn the background color black
		glViewport(0, 0, w(), h());                               // Make our viewport the whole window
		glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
		glLoadIdentity();                                      // Reset The Projection Matrix
		//gluOrtho2D(-10,10,-10,10);                             // (xmin,xmax,ymin,ymax)
		gluPerspective(45.0f, w() / h(), 1.0f, 150.0f);
		glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
		glLoadIdentity();                                      // Reset The Modelview Matrix
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
		glLoadIdentity();                                      // Reset The View
		//0,0, 10, 0, 0, 0, 0, 1, 0
		gluLookAt(0, -15, 0, 0, 0, 0, 0, 0, 1);        // Position - View  - Up Vector
		glEnable(GL_DEPTH_TEST);

		panel_opengl::draw(vertices);
		valid(1);
	}

	panel_opengl::update();
}



