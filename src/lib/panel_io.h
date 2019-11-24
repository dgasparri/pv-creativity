#pragma once

#include <vector>
#include <iostream>
#include "panel_geometry_fp.h"


std::vector<p_geometry::vertex> load_vertices(std::string filename);
std::vector<p_geometry::vertex> test_vertices();