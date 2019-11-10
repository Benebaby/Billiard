#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <string>
#include "Triangle.h"
#include "Sphere.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"

class Scene
{
private:
	GLuint ssbot, ssbos, ssbom;
	std::vector<Triangle> triangles;
	std::vector<Sphere> spheres;
	std::vector<Material> materials;
	void proofCollision(Sphere& s1, int s1Index, float deltaTime);
public:
	Scene(GLuint ProgramID);
	void addSphere(Sphere s);
	void addTriangle(Triangle t);
	void addMaterial(Material m);
	void addMesh(Mesh mesh);
	void createStartTri(glm::vec2 pos, float offset);
	void createRandomBalls(int xcount, int zcount, float velocity);
	void update(float deltaTime);
	void render();
};

