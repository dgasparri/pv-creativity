#include "../../pv-creativity/src/plot/gnuplot.h"
#include <iostream>
#include <windows.h>


void sa_gnuplot::plot() {

	char* currentpath;
	_get_pgmptr(&currentpath);
	std::cout << "dentro plot - " << currentpath << "\n";


	Gnuplot gp;
	gp << R"(
        set terminal wxt size 1000,1000 enhanced font 'Verdana,20'
        set title 'Solar Absorption'
        set xlabel 'Day of year'
        set ylabel 'Hour'
        set xrange[1:36]
        set yrange[9:18]
        set palette
        set pm3d at s
        splot 'C:\\Users\\andre\\source\\repos\\pv-creativity\\pv-creativity\\outputS.txt' with lines
    )";
}
