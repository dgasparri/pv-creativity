#include "test_vertices_fp.h"


const std::vector<geometry::vertex *> panel_io::test_vertices()
{
	std::vector<geometry::vertex *> vertices;

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 3.0));

	return vertices;

}

const std::vector<geometry::vertex *> panel_io::test_vertices_2()
{
	std::vector<geometry::vertex *> vertices;

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(3.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	return vertices;

}

const std::vector<geometry::vertex *> panel_io::test_vertices_zrotated()
{
	std::vector<geometry::vertex *> vertices;

	vertices.emplace_back(new geometry::vertex(-3.0, 0.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(0.0, -3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(3.0, 0.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(3.0, 0.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	vertices.emplace_back(new geometry::vertex(0.0, 3.0, 0.0));
	vertices.emplace_back(new geometry::vertex(-3.0, 0.0, 0.0));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, 2.0));

	return vertices;

}
