#include "Material.h"

Material::Material(glm::vec4 diffuse, glm::vec3 specular, float shininess, float reflectance)
{
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shininess;
	m_reflectance = reflectance;
	diffuseTexture = -1;
	m_materialType = 0;
}

Material::Material(int diffuseTextureID, glm::vec3 specular, float shininess, float reflectance)
{
	diffuseTexture = glGetTextureHandleARB(diffuseTextureID);
	glMakeTextureHandleResidentARB(diffuseTexture);
	m_specular = specular;
	m_shininess = shininess;
	m_reflectance = reflectance;
	m_materialType = 1;
}
