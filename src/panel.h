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



namespace panel {
    void draw(void);
    void update(void);
}
