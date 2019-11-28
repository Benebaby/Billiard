#pragma once
#include <Tools/Defs.h>
#include <string>
#include <vector>
#include <fstream>
#include "Triangle.h"

class Mesh {
private:
	std::string m_filename;
	int m_MatID;
	std::vector<Triangle> m_polygons;
	void readObj(std::string filename);
public:
	Mesh(std::string filename, int matID);
	std::vector<Triangle> getPolygons();
};
