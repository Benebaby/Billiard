#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <Tools/ShaderSet.h>
#include <Tools/CompatibilityTools.h>

#include "Texture.h"
#include "Camera.h"
#include "ScreenQuad.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"

#define WIDTH 1600
#define HEIGHT 900
#define FOV 45.

GLFWwindow* window;
Camera* cam = new Camera(WIDTH, HEIGHT, FOV);
ShaderSet* rayTracerProgram;
ShaderSet* showImageProgram;
ScreenQuad* quad;
Texture* image;
Texture* test;
Scene* scene;
GLuint loc_from, loc_xvec, loc_yvec, loc_zvec, loc_lightPos, loc_Eye, loc_image_size, loc_image, loc_FOV;
glm::vec4 light = glm::vec4(39.298245f, 39.298245f, 19.649122f, 1.0f);

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	cam->updateRadius(yoffset);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		cam->updateCamPos(xpos, ypos, true);
	else
		cam->updateCamPos(xpos, ypos, false);
}

void resizeCallback(GLFWwindow * window, int w, int h)
{
	image = new Texture(w, h, 4);
	glViewport(0, 0, w, h);
}

void initWindow() {
	glfwInit();
	CompatibilityTools::useOpenGL33CoreProfile();
	window = glfwCreateWindow(WIDTH, HEIGHT, "RayTracerGPU", NULL, NULL);
	glfwSetWindowPos(window, 150, 90);
	glfwSetCursorPosCallback(window, &MouseCallback);
	glfwSetScrollCallback(window, &ScrollCallback);
	glfwSetWindowSizeCallback(window, &resizeCallback);
	glfwMakeContextCurrent(window);
	glewInit();
	CompatibilityTools::checkCompatibility();
}

void initOpenGL() {
	const char* showImageFiles[2] = { SHADERS_PATH"/RayTracerGPU/showImage.vert", SHADERS_PATH"/RayTracerGPU/showImage.frag" };
	showImageProgram = new ShaderSet(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, showImageFiles);

	const char* rayTracerFiles[2] = { SHADERS_PATH "/RayTracerGPU/rayTracerOptimized.comp" };
	rayTracerProgram = new ShaderSet(COMPUTE_SHADER_BIT, rayTracerFiles);

	rayTracerProgram->UseProgram();
	loc_from = glGetUniformLocation(rayTracerProgram->getProgramID(), "from");
	loc_xvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "xvec");
	loc_yvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "yvec");
	loc_zvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "zvec");
	loc_lightPos = glGetUniformLocation(rayTracerProgram->getProgramID(), "lightPos");
	loc_Eye = glGetUniformLocation(rayTracerProgram->getProgramID(), "eye");
	loc_FOV = glGetUniformLocation(rayTracerProgram->getProgramID(), "fov");
	loc_image_size = glGetUniformLocation(rayTracerProgram->getProgramID(), "image_size");
	loc_image = glGetUniformLocation(rayTracerProgram->getProgramID(), "image");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	std::cout << "** ComputeShader Specs **" << std::endl;
	scene = new Scene(rayTracerProgram->getProgramID());
	quad = new ScreenQuad();
	image = new Texture(WIDTH, HEIGHT, 4);
	GLint data = 0;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_SIZE: " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &data);
	std::cout << " * " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &data);
	std::cout << " * " << data << std::endl;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_COUNT: " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &data);
	std::cout << " * " << data;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &data);
	std::cout << " * " << data << std::endl;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &data);
	std::cout << "GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS: " << data << std::endl;
	glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &data);
	std::cout << "GL_MAX_COMPUTE_SHARED_MEMORY_SIZE: " << data / 1024 << "KB" << std::endl;
}

void rayTraceImage()
{
	rayTracerProgram->UseProgram();
	glm::vec3 from, xvec, yvec, zvec;
	cam->getView(&xvec, &yvec, &zvec, &from);
	glm::vec3 eye = cam->getEye();
	glUniform3f(loc_from, from.x, from.y, from.z);
	glUniform3f(loc_xvec, xvec.x, xvec.y, xvec.z);
	glUniform3f(loc_yvec, yvec.x, yvec.y, yvec.z);
	glUniform3f(loc_zvec, zvec.x, zvec.y, zvec.z);
	glUniform4f(loc_lightPos, light.x, light.y, light.z, light.w);
	glUniform3f(loc_Eye, eye.x, eye.y, eye.z);
	glUniform1f(loc_FOV, cam->getFov());
	scene->render();
	glUniform2i(loc_image_size, image->getWidth(), image->getHeight());
	glBindImageTexture(0, image->getTextureID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glUniform1i(loc_image, 0);
	glDispatchCompute(image->getWidth() / 32 + 1, image->getHeight() / 32 + 1, 1);
}

void showImage() {
	showImageProgram->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	image->bind2D();
	quad->render();
	image->unbind2D();
}

int main(void)
{
	initWindow();
	initOpenGL();



	scene->createStartTri(glm::vec2(-20.503432, 0.0f), 0.05f);
	scene->addSphere(Sphere(glm::vec3(20.503432, 1.0f, 0.0f), 1.0f, glm::vec3(-40.0f, 0.0f, glm::linearRand(-0.5f, 0.5f)), 15));
	scene->addMesh(Mesh("/models/box.obj"));

	float ballreflectivness = 0.1f;
	scene->addMaterial(Material(Texture("/textures/billiard_1.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_2.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_3.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_4.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_5.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_6.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_7.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_8.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_9.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_10.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_11.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_12.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_13.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_14.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/billiard_15.png").getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(glm::vec4(0.964843f, 0.945312f, 0.828125f, 1.0f), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/Tiles.png").getTextureID(), glm::vec3(1.0f), 100.0f, 0.15f));

	double time = glfwGetTime();
	double deltaTime;
	bool moveON = false;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		if (glfwGetKey(window, GLFW_KEY_U)) {
			moveON = true;
		}

		if(moveON)
			scene->update(deltaTime);

		rayTraceImage();
		showImage();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
