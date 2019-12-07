#include "gnuplot.h"
#include <iostream>
#include <windows.h>

 
void sa_gnuplot::plot() {
    
    char *currentpath;
    _get_pgmptr(&currentpath);
    std::cout<<"dentro plot - "<<currentpath<<"\n";


    Gnuplot gp;
    gp << R"(
        set terminal wxt size 1000,1000 enhanced font 'Verdana,20'
        set title 'Solar Absorption'
        set xlabel 'Day of year'
        set ylabel 'Hour'
        set xrange[1:365]
        set yrange[9:18]
        set palette
        set pm3d at s
        splot 'C:\\Users\\dmg\\C++\\repos\\pv-creativity\\src\\plot\\data.txt' with lines
    )";
}

