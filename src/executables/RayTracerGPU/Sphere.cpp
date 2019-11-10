#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, glm::mat3 rotation, int matID)
{
	m_matID = matID;
	m_position = position;
	m_radius = radius;
	m_rotation[0] = glm::vec4(rotation[0], 0.0f);
	m_rotation[1] = glm::vec4(rotation[1], 0.0f);
	m_rotation[2] = glm::vec4(rotation[2], 0.0f);
	m_moveDir = glm::vec3(0.0f);
}

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 moveDir, int matID)
{
	m_matID = matID;
	m_position = position;
	m_radius = radius;
	m_rotation = glm::mat3x4(1.0f);
	m_moveDir = moveDir;
}

Sphere::Sphere(glm::vec3 position, float radius, int matID)
{
	m_matID = matID;
	m_position = position;
	m_radius = radius;
	m_rotation = glm::mat3x4(1.0f);
	m_moveDir = glm::vec3(0.0f);
}

void Sphere::setMoveDir(glm::vec3 moveDir)
{
	m_moveDir = moveDir;
}

void Sphere::setPosition(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 Sphere::getMoveDir()
{
	return m_moveDir;
}

glm::vec3 Sphere::getPosition()
{
	return m_position;
}

float Sphere::getRadius()
{
	return m_radius;
}

void Sphere::update(float deltaTime)
{
	float velocity = glm::length(m_moveDir);
	if (velocity > 0) {
		glm::vec3 dir = glm::normalize(m_moveDir);
		glm::vec3 rotateAxis = glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f));
		float degrees = deltaTime * 360.0f / (float)(3.141592 * 2.0f * m_radius) * velocity;
		glm::mat3 rotation = glm::rotate(glm::mat4(m_rotation), glm::radians(degrees), rotateAxis);
		glm::vec3 translation = deltaTime * m_moveDir;
		m_position += translation;
		m_rotation[0] = glm::vec4(rotation[0], 0.0f);
		m_rotation[1] = glm::vec4(rotation[1], 0.0f);
		m_rotation[2] = glm::vec4(rotation[2], 0.0f);
	}
}
