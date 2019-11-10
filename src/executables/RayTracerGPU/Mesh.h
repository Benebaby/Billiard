#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <string>
#include <vector>
#include <iostream>
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
