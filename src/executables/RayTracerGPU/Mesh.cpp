#include "Mesh.h"

std::vector<std::string> split(std::string str) {
	std::string sep = " ";
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

std::vector<float> splitF(std::string str) {
	std::string sep = " ";
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<float> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(std::stof(current));
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

std::vector<int> splitI(std::string str, std::string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<int> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(std::stoi(current));
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

void Mesh::readObj(std::string filename) {
	double a = glfwGetTime();
	std::vector<glm::vec3> V, N;
	std::vector<glm::vec2> T;
	std::vector<int> TempI;
	std::vector<float> TempF;
	std::vector<std::string> TempS;
	std::string line;
	glm::vec3 temp(0.0f);
	glm::vec2 tempt(0.0f);
	std::vector<glm::vec3> m_vertecies;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texCoords;

	int i = 0, j = 0, k = 0, f = 0;
	std::ifstream inFile(RESOURCES_PATH + filename);
	while (getline(inFile, line))
	{
		if (line[0] == 'v') {
			if (line[1] == 't') {
				TempF = splitF(line.substr(3));
				tempt.x = TempF[0];
				tempt.y = TempF[1];
				T.push_back(tempt);
				k++;
			}
			else if (line[1] == 'n') {
				TempF = splitF(line.substr(3));
				temp.x = TempF[0];
				temp.y = TempF[1];
				temp.z = TempF[2];
				N.push_back(temp);
				j++;
			}
			else {
				TempF = splitF(line.substr(2));
				temp.x = TempF[0];
				temp.y = TempF[1];
				temp.z = TempF[2];
				V.push_back(temp);
				i++;
			}
		}
		else if (line[0] == 'f') {
			TempS = split(line.substr(2));
			for (unsigned int i = 0; i < TempS.size(); i++) {
				TempI = splitI(TempS[i], "/");
				if (T.size() != 0) {
					m_vertecies.push_back(V[TempI[0] - 1]);
					m_texCoords.push_back(T[TempI[1] - 1]);
					m_normals.push_back(N[TempI[2] - 1]);
				}
				else {
					m_vertecies.push_back(V[TempI[0] - 1]);
					m_normals.push_back(N[TempI[1] - 1]);
				}
			}
			f++;
		}
	}
	double b = glfwGetTime();
	inFile.close();
	for (int x = 0; x < m_vertecies.size(); x = x+3)
	{
		m_polygons.push_back(Triangle(m_vertecies[x], m_vertecies[x + 1], m_vertecies[x + 2], m_normals[x], m_normals[x + 1], m_normals[x + 2], m_texCoords[x] * 8.0f, m_texCoords[x + 1] * 8.0f, m_texCoords[x + 2] * 8.0f, m_MatID));
	}
	std::cout << "Mesh " << filename << " loaded with: " << i << " vertecies, " << j << " normals, " << k << " texcoords, " << f << " triangles" << std::endl;
	std::cout << b - a << " sec to read file :)" << std::endl;
}

Mesh::Mesh(std::string filename, int matID)
{
	m_MatID = matID;
	m_filename = filename;
	readObj(filename);
}

std::vector<Triangle> Mesh::getPolygons()
{
	return m_polygons;
}
