#include "Scene.h"

Scene::Scene(GLuint ProgramID) {
	glGenBuffers(1, &ssbos);
	glGenBuffers(1, &ssbot);
	glGenBuffers(1, &ssbom);
}

void Scene::addSphere(Sphere s) {
	spheres.push_back(s);
}

void Scene::addTriangle(Triangle t)
{
	triangles.push_back(t);
}

void Scene::addMaterial(Material m)
{
	materials.push_back(m);
}

void Scene::addMesh(Mesh mesh)
{
	std::vector<Triangle> b = mesh.getPolygons();
	triangles.reserve(triangles.size() + b.size());
	triangles.insert(triangles.end(), b.begin(), b.end());
	b.clear();
}

void Scene::createStartTri(glm::vec2 pos, float offset)
{
	std::vector<int> balls(14);
	for (int i = 0; i < 14; i++) {
		if (i > 6)
			balls[i] = i + 1;
		else
			balls[i] = i;
	}
	float offx = sqrt(3) + (float)(offset * 2.0f);
	float offz = 2.0f + offset * 2.0f;
	int matID = 0;
	srand(time(0));

	matID = static_cast<int>(glm::linearRand(0, 13) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 4 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 2.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID]));  balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 12) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 4 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 1.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 11) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 4 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 0.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 10) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 4 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 1.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 9) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 4 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 2.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 8) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 3 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 1.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 7) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 3 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 0.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 6) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 3 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 0.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 5) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 3 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 1.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 4) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 2 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 1.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);

	addSphere(Sphere(glm::vec3(pos.x - offx * 2 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 0.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), 7));
	matID = static_cast<int>(glm::linearRand(0, 3) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 2 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 1.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 2) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 1 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 0.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = static_cast<int>(glm::linearRand(0, 1) + 0.5f);
	addSphere(Sphere(glm::vec3(pos.x - offx * 1 + glm::linearRand(-offset, offset), 1.0f, pos.y - offz * 0.5f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
	matID = 0;
	addSphere(Sphere(glm::vec3(pos.x - offx * 0 + glm::linearRand(-offset, offset), 1.0f, pos.y + offz * 0.0f + glm::linearRand(-offset, offset)), 1.0f, glm::mat3(glm::rotate(glm::mat4(1.0f), glm::linearRand(0.0f, 360.0f), glm::ballRand(1.0f))), balls[matID])); balls.erase(balls.begin() + matID);
}

void Scene::createRandomBalls(int xcount, int zcount, float velocity)
{
	glm::vec2 move;
	glm::vec2 pos;
	for (int i = 0; i < xcount; i++) {
		pos.x = i * (76.0f / (xcount - 1)) - 38.0f;
		for (int j = 0; j < zcount; j++) {
			pos.y = j * (36.0f / (zcount - 1)) - 18.0f;
			move = glm::circularRand(velocity);
			addSphere(Sphere(glm::vec3(pos.x, 1.0f, pos.y), 1.0f, glm::vec3(move.x, 0.0f, move.y), static_cast<int>(glm::linearRand(0, 14) + 0.5f)));
		}
	}
}

void Scene::proofCollision(Sphere & s1, int s1Index, float deltaTime) {
	for (int i = 0; i < spheres.size(); i++)
	{
		glm::vec3 nextPosition = s1.getPosition() + deltaTime * s1.getMoveDir();
		float distance = glm::length(nextPosition - spheres[i].getPosition());
		float radiusAdd = s1.getRadius() + spheres[i].getRadius();
		if (distance <= radiusAdd && s1Index != i) {
			glm::vec2 v1 = glm::vec2(s1.getMoveDir().x, s1.getMoveDir().z);
			glm::vec2 x1 = glm::vec2(s1.getPosition().x, s1.getPosition().z);
			glm::vec2 v2 = glm::vec2(spheres[i].getMoveDir().x, spheres[i].getMoveDir().z);
			glm::vec2 x2 = glm::vec2(spheres[i].getPosition().x, spheres[i].getPosition().z);
			glm::vec2 move1 = v1 - (glm::dot(v1 - v2, x1 - x2) / (glm::length(x1 - x2) * glm::length(x1 - x2))) * (x1 - x2);
			glm::vec2 move2 = v2 - (glm::dot(v2 - v1, x2 - x1) / (glm::length(x2 - x1) * glm::length(x2 - x1))) * (x2 - x1);
			s1.setMoveDir(glm::vec3(move1.x, 0.0f, move1.y));
			spheres[i].setMoveDir(glm::vec3(move2.x, 0.0f, move2.y));
		}
	}
}

void Scene::update(float deltaTime)
{
	for (int i = 0; i < spheres.size(); i++)
	{
		glm::vec3 nextPosition = spheres[i].getPosition() + deltaTime * spheres[i].getMoveDir();
		float velocity = glm::length(spheres[i].getMoveDir());
		glm::vec3 dir = glm::normalize(spheres[i].getMoveDir());
		if (nextPosition.z < -18.649122f) {
			spheres[i].setMoveDir(glm::reflect(velocity * dir, glm::vec3(0.0f, 0.0f, 1.0f)));
		}if (nextPosition.z > 18.649122f) {
			spheres[i].setMoveDir(glm::reflect(velocity * dir, glm::vec3(0.0f, 0.0f, -1.0f)));
		}if (nextPosition.x < -38.298245f) {
			spheres[i].setMoveDir(glm::reflect(velocity * dir, glm::vec3(1.0f, 0.0f, 0.0f)));
		}if (nextPosition.x > 38.298245f) {
			spheres[i].setMoveDir(glm::reflect(velocity * dir, glm::vec3(-1.0f, 0.0f, 0.0f)));
		}
		proofCollision(spheres[i], i, deltaTime);

		spheres[i].update(deltaTime);
	}
}

void Scene::render() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos);
	glBufferData(GL_SHADER_STORAGE_BUFFER, spheres.size() * sizeof(Sphere), spheres.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbos);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbot);
	glBufferData(GL_SHADER_STORAGE_BUFFER, triangles.size() * sizeof(Triangle), triangles.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbot);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbom);
	glBufferData(GL_SHADER_STORAGE_BUFFER, materials.size() * sizeof(Material), materials.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbom);
}