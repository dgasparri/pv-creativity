#pragma once
#include <windows.h>
#include <FL/gl.h>
//#include <GL/glu.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "panel_geometry_fp.h"

#define CARTESIO  1
#define PANEL  2

//extern std::vector<p_geometry::vertex> vertices;

namespace panel {
    void draw(void);
    void update(void);
}
