#include "Triangle.h"

Triangle::Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, int matID)
{
	m_matID = matID;
	m_A = A;
	m_u = B - A;
	m_v = C - A;
	m_normal = glm::cross(m_u, m_v);
	m_na = glm::vec3(0.0f); m_nb = glm::vec3(0.0f); m_nc = glm::vec3(0.0f);
	m_ta = glm::vec2(0.0f); m_tb = glm::vec2(0.0f); m_tc = glm::vec2(0.0f);
	m_hasNormals = false;
	pad0 = 0; pad1 = 0; pad2 = 0; pad3 = 0; pad4 = 0; pad5 = glm::vec2(0.0f);
}

Triangle::Triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 na, glm::vec3 nb, glm::vec3 nc, glm::vec2 ta, glm::vec2 tb, glm::vec2 tc, int matID)
{
	m_matID = matID;
	m_A = A;
	m_u = B - A;
	m_v = C - A;
	m_na = na; m_nb = nb; m_nc = nc;
	m_ta = ta; m_tb = tb; m_tc = tc;
	m_hasNormals = true;
	pad0 = 0; pad1 = 0; pad2 = 0; pad3 = 0; pad4 = 0; pad5 = glm::vec2(0.0f);
}
