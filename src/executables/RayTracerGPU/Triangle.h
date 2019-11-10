#pragma once
#include <glm/glm.hpp>

class Triangle
{
private:
	glm::vec3 m_A;
	float pad0;
	glm::vec3 m_u;
	float pad1;
	glm::vec3 m_v;
	float pad2;
	glm::vec3 m_normal;
	int m_matID;
	glm::vec3 m_na;
	bool m_hasNormals;
	glm::vec3 m_nb;
	float pad3;
	glm::vec3 m_nc;
	float pad4;
	glm::vec2 m_ta;
	glm::vec2 m_tb;
	glm::vec2 m_tc;
	glm::vec2 pad5;

public:
	Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, int matID);
	Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 na, glm::vec3 nb, glm::vec3 nc, glm::vec2 ta, glm::vec2 tb, glm::vec2 tc, int matID);
};