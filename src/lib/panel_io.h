#pragma once

#include <vector>
#include <iostream>
#include "panel_geometry_fp.h"

namespace panel_io {
	const std::vector<p_geometry::vertex *> load_vertices(std::string filename);
	const std::vector<p_geometry::vertex *> test_vertices();
}
