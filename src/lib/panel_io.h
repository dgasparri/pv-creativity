#pragma once

#include <vector>
#include <iostream>
#include "geometry_fp.h"

namespace panel_io {
	bool load_vertices(const std::string filename, std::vector<geometry::vertex *> *v);
	//const std::vector<geometry::vertex *> load_vertices(std::string filename);
	const std::vector<geometry::vertex *> test_vertices();
	const std::vector<geometry::vertex *> test_vertices_2();
}
