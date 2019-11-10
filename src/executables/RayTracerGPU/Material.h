#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Material
{
public:
	Material(glm::vec4 diffuse, glm::vec3 specular, float shininess, float reflectance);
	Material(int diffuseTextureID, glm::vec3 specular, float shininess, float reflectance);
private:
	glm::vec4 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;
	int m_materialType;
	float m_reflectance; 
	GLuint64 diffuseTexture;
};