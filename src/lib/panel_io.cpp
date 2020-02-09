#include "panel_io.h"

const std::vector<geometry::vertex *> panel_io::load_vertices(const std::string filename)
{
	std::vector<geometry::vertex *> v;
	float v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z, direction;
	FILE* fp;
	if (0 != fopen_s(&fp, filename.c_str(), "r")) {
		std::cout << "Unable to open file: " << filename << std::endl;
		return v;
	}

	int assigned;
	do {
		assigned = fscanf_s(fp, "%f %f %f, %f %f %f, %f %f %f,%f\n", &v1x, &v1y, &v1z, &v2x, &v2y, &v2z, &v3x, &v3y, &v3z, &direction);
		
		if (assigned < 10 || assigned == EOF)
			break;
		v.emplace_back(new geometry::vertex(v1x, v1y, v1z, direction));
		v.emplace_back(new geometry::vertex(v2x, v2y, v2z, direction));
		v.emplace_back(new geometry::vertex(v3x, v3y, v3z, direction));

	} while (true);

	fclose(fp);
	return v;
}



const std::vector<geometry::vertex *> panel_io::test_vertices_2()
{
	std::vector<geometry::vertex *> vertices;
	double L = 3;
	double V = 4;
	vertices.emplace_back(new geometry::vertex(-V, -L, 0.0, 1));
	vertices.emplace_back(new geometry::vertex(V, -L, 0.0, 1));
	vertices.emplace_back(new geometry::vertex(0.0, 0.0, V, 1));

	return vertices;

}
