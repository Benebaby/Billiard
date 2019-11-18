#pragma once
#include <Tools/Defs.h>
#include <string>
#include <vector>
#include <fstream>
#include "Triangle.h"

class Mesh {
private:
	std::string m_filename;
	std::vector<Triangle> m_polygons;
	void readObj(std::string filename);
public:
	Mesh(std::string filename);
	std::vector<Triangle> getPolygons();
};
