#pragma once
#include <glm/ext.hpp>

class Sphere
{
private:
	glm::vec3 m_position;
	int m_matID;
	glm::mat3x4 m_rotation;
	float m_radius;
	glm::vec3 m_moveDir;
public:
	Sphere(glm::vec3 position, float radius, glm::mat3 rotation, int matID);
	Sphere(glm::vec3 position, float radius, glm::vec3 moveDir, int matID);
	Sphere(glm::vec3 position, float radius, int matID);
	void setMoveDir(glm::vec3 moveDir);
	void setPosition(glm::vec3 position);
	glm::vec3 getMoveDir();
	glm::vec3 getPosition();
	float getRadius();
	void update(float deltaTime);
};

