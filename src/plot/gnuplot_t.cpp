// http://gnuplot.sourceforge.net/demo/pm3d.html

// https://www.youtube.com/watch?v=BFA_o1KMyg8
// https://www.youtube.com/watch?v=OByVkOVqRl4
// https://alvinalexander.com/technology/gnuplot-charts-graphs-examples

//https://sourceforge.net/p/gnuplot/discussion/5925/thread/c06efa15/ -> You need a blank line every time the x value changes.
// https://alvinalexander.com/technology/gnuplot-charts-graphs-examples

/*gnuplot> 
set title "Solar Absorption"
set xlabel "Day"
set ylabel "Hour"
set xrange[1:365]
set yrange[9:18]
set pm3d; set palette
splot 'data.txt' with lines
set pm3d at s
splot 'data.txt' with lines
set zrange[180:1200]
splot 'data.txt' with lines
set pm3d at b
splot 'data.txt' with lines
*/


#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using Callback = void(*)(Fl_Widget*, void*);

int w{Fl::w()/2}, h{Fl::h()};
struct Windows;



struct Widget {
	int width, height;
	string label;
	Point xy;
	Callback do_it;
	Windows *own;
	Widget(Point p, int w, int h, string s, Callback cb)
	: xy(p), width(w), height(h), label(s), do_it(cb) {}
	virtual void attach(Windows&) {}
};


struct Windows : Fl_Double_Window {
	Windows(Point topleft, int width, int height, string title)
	: Fl_Double_Window(topleft.x, topleft.y, width, height, title.c_str()) {
		color(FL_BLACK);
		show();
	}
	vector<Shape*> shapes;
	void attach(Shape& s) { shapes.push_back(&s); }
	void attach(Widget& w) {
		begin();
		w.attach(*this);
		end();
	}
	void draw() {
		Fl_Double_Window::draw();
	}
};


#include "gnuplot-iostream.h"

void callback2(Fl_Widget*, void*) {
	Gnuplot gp;
	gp << R"(
		set terminal wxt size 1000,1000 enhanced font 'Verdana,20'
		set title 'Collisions vs Time'
		set xlabel 'Time (s)'
		set ylabel 'Collisions'
		plot 'collisions_vs_time.txt' w l lw 3 notitle
	)";
}




Windows window(Point(w, 0), w, h, "Part5");

struct Button : Widget {
	Fl_Button* pw;
	Button(Point p, int w, int h, string s, Callback cb)
	: Widget(p, w, h, s, cb) {}
	void attach(Windows &window) {
		pw = new Fl_Button(xy.x, xy.y, width, height, label.c_str());
		pw->callback(do_it);
		pw->color(FL_DARK_BLUE);
		pw->labelfont(FL_COURIER_BOLD_ITALIC);
		pw->labelcolor(FL_WHITE);
		pw->labelsize(14);
		own = &window;
	}
};

Button button2(Point(w/2+200,200),100,30,"PLOT",callback2);

int main() {
	window.attach(outbox1);
	window.attach(outbox2);
	window.attach(button2);

	slider1.set_value(500);
	slider1.set_bounds(100,1000);
	inbox1.set_value("10");
	outbox1.set_value("0");
	outbox2.set_value("0");
	return Fl::run();
}