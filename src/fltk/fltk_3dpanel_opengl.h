#pragma once
#include <windows.h>
#include <FL/gl.h>
//#include <GL/glu.h>
#include <math.h>
#include <vector>
#include "../lib/geometry_fp.h"

#define CARTESIO  1
#define PANEL  2


namespace fltk_3dpanel_opengl {
    void draw(const std::vector<geometry::vertex *> &vertices);
    void update();
}