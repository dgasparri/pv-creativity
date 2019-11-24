#include "panel_io.h"


std::vector<p_geometry::vertex> load_vertices(std::string filename)
{
    std::vector<p_geometry::vertex> v;
	float v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
    FILE *fp;
    if(0!=fopen_s (&fp, filename.c_str(), "r")) {
        std::cout<<"Unable to open file: "<<filename<<std::endl;
        return v;
    }

    int assigned;
    do {
        assigned = fscanf_s(fp, "%f %f %f, %f %f %f, %f %f %f\n", &v1x, &v1y, &v1z, &v2x, &v2y, &v2z, &v3x, &v3y, &v3z);
        std::cout<<"Assigned: "<<assigned<<std::endl;
        if(assigned < 9 || assigned==EOF) 
            break;
		v.emplace_back(p_geometry::vertex(v1x, v1y, v1z));
		v.emplace_back(p_geometry::vertex(v2x, v2y, v2z));
		v.emplace_back(p_geometry::vertex(v3x, v3y, v3z));
        std::cout<<"X: "<<v1x<<" Y: "<<v1y<<" Z: "<<v1z<<std::endl;
        std::cout<<"X: "<<v2x<<" Y: "<<v2y<<" Z: "<<v2z<<std::endl;
        std::cout<<"X: "<<v3x<<" Y: "<<v3y<<" Z: "<<v3z<<std::endl;

    } while(true);

    fclose(fp);
	return v;
}



std::vector<p_geometry::vertex> test_vertices()
{
    std::vector<p_geometry::vertex> vertices;

	vertices.emplace_back(p_geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 3.0, -3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));

	vertices.emplace_back(p_geometry::vertex(-3.0, -3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex(-3.0,  3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));

	vertices.emplace_back(p_geometry::vertex( 3.0,  3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex(-3.0,  3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));

	vertices.emplace_back(p_geometry::vertex( 3.0,  3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 3.0, -3.0, 0.0));
	vertices.emplace_back(p_geometry::vertex( 0.0,  0.0, 1.5));

	return vertices;

}
