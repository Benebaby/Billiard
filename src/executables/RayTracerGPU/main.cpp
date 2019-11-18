#include <Tools/Defs.h>
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
#include "Light.h"

#define WIDTH 1600
#define HEIGHT 900
#define FOV 45.

GLFWwindow *window;
Camera *cam = new Camera(WIDTH, HEIGHT, FOV);
ShaderSet *rayTracerProgram;
ShaderSet *showImageProgram;
ScreenQuad *quad;
Texture *image;
Texture *test;
Scene *scene;
GLuint loc_from, loc_xvec, loc_yvec, loc_zvec, loc_Eye, loc_image_size, loc_image, loc_FOV;

void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	cam->updateRadius(yoffset);
}

void MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		cam->updateCamPos(xpos, ypos, true);
	else
		cam->updateCamPos(xpos, ypos, false);
}

void resizeCallback(GLFWwindow *window, int w, int h)
{
	image = new Texture(w, h, 4);
	glViewport(0, 0, w, h);
}

void initWindow()
{
	glfwInit();
	CompatibilityTools::useOpenGL33CoreProfile();
	window = glfwCreateWindow(WIDTH, HEIGHT, "RayTracerGPU", NULL, NULL);
	glfwSetWindowPos(window, 150, 90);
	glfwSetCursorPosCallback(window, &MouseCallback);
	glfwSetScrollCallback(window, &ScrollCallback);
	glfwSetWindowSizeCallback(window, &resizeCallback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glewInit();
}

void initOpenGL()
{
	const char *showImageFiles[2] = {SHADERS_PATH "/RayTracerGPU/showImage.vert", SHADERS_PATH "/RayTracerGPU/showImage.frag"};
	showImageProgram = new ShaderSet(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, showImageFiles);

	const char *rayTracerFiles[2] = {SHADERS_PATH "/RayTracerGPU/rayTracerBindless.comp"};
	rayTracerProgram = new ShaderSet(COMPUTE_SHADER_BIT, rayTracerFiles);

	rayTracerProgram->UseProgram();
	loc_from = glGetUniformLocation(rayTracerProgram->getProgramID(), "from");
	loc_xvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "xvec");
	loc_yvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "yvec");
	loc_zvec = glGetUniformLocation(rayTracerProgram->getProgramID(), "zvec");
	loc_Eye = glGetUniformLocation(rayTracerProgram->getProgramID(), "eye");
	loc_FOV = glGetUniformLocation(rayTracerProgram->getProgramID(), "fov");
	loc_image_size = glGetUniformLocation(rayTracerProgram->getProgramID(), "image_size");
	loc_image = glGetUniformLocation(rayTracerProgram->getProgramID(), "image");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	scene = new Scene(rayTracerProgram->getProgramID());
	quad = new ScreenQuad();
	image = new Texture(WIDTH, HEIGHT, 4);
	CompatibilityTools::checkCompatibility();
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
	glUniform3f(loc_Eye, eye.x, eye.y, eye.z);
	glUniform1f(loc_FOV, cam->getFov());
	scene->render();
	glUniform2i(loc_image_size, image->getWidth(), image->getHeight());
	glBindImageTexture(0, image->getTextureID(), 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glUniform1i(loc_image, 0);
	glDispatchCompute(image->getWidth() / 32 + 1, image->getHeight() / 32 + 1, 1);
}

void showImage()
{
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
	scene->addLight(Light(1, glm::vec3(-26.19883f, 19.649122, 0.0f), glm::vec3(1.0f, 0.839215f, 0.666666f)));
	scene->addLight(Light(1, glm::vec3(0.0f, 19.649122, 0.0f), glm::vec3(1.0f, 0.839215f, 0.666666f)));
	scene->addLight(Light(1, glm::vec3(26.19883f, 19.649122, 0.0f), glm::vec3(1.0f, 0.839215f, 0.666666f)));
	// scene->addLight(Light(1, glm::vec3(-26.19883f, 19.649122, 0.0f), glm::vec3(1.f, 0.f, 0.f)));
	// scene->addLight(Light(1, glm::vec3(0.0f, 19.649122, 0.0f), glm::vec3(0.f, 1.f, 0.f)));
	// scene->addLight(Light(1, glm::vec3(26.19883f, 19.649122, 0.0f), glm::vec3(0.f, 0.f, 1.f)));
	float ballreflectivness = 0.2f;
	for (unsigned int i = 1; i < 16; i++)
	{
		std::string path = "/textures/billiard_" + std::to_string(i) + ".png";
		scene->addMaterial(Material(Texture(path).getTextureID(), glm::vec3(1.0f), 100.0f, ballreflectivness));
	}
	scene->addMaterial(Material(glm::vec4(0.964843f, 0.945312f, 0.828125f, 1.0f), glm::vec3(1.0f), 100.0f, ballreflectivness));
	scene->addMaterial(Material(Texture("/textures/marble_dark.png").getTextureID(), glm::vec3(1.0f), 100.0f, 0.2f));

	double time = glfwGetTime();
	double deltaTime;
	bool moveON = false;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		deltaTime = glfwGetTime() - time;
		time = glfwGetTime();

		if (glfwGetKey(window, GLFW_KEY_U))
		{
			moveON = true;
		}

		if (moveON)
			scene->update((float)deltaTime);

		rayTraceImage();
		showImage();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
