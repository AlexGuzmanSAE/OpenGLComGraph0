#pragma once
#include <glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "string"
#include "map"
#include "Plane.h"

class Application
{
	std::map<std::string, GLuint> mapShaders;
	std::map<std::string, GLuint> mapGeometry;
	std::map<std::string, GLint> mapUniforms;
	std::map<std::string, GLint> mapTextures;

	glm::mat4 projection;
	glm::mat4 camera;
	glm::mat4 accumTrans;
	glm::mat4 accumTransRotationX;
	glm::mat4 accumTransRotationY;
	glm::vec3 eye{ 0.0f, 0.0f, 2.0f };
	float eyeXRot{}, eyeYRot{};
	float lightXMove{}, lightYMove{};
	glm::vec3 center;

	void SetUpShaderPassthru();
	void SetUpShaderTransforms();
	void SetUpShaders();
	void SetUpGeometry();
	void SetUpGeometrySingleArray();
	void SetupPlane();
	GLuint SetUpTexture(const std::string& filename);

	float time{0.0f};
	float amplitude{ 0.125f };
	float frecuence{ 17.0f };
	
	float interpolateVal{};

	Plane plane;

public:
	float r{ 1 }, g{ 1 }, b{ 1 }, a{ 1 };
	GLFWwindow* window;
	//void check_keyboard( int key, int scancode, int action, int mods);
	//void check_keyboard_2(GLFWwindow* window, int key, int scancode, int action, int mods);
	void SetUp();
	void Update();
	void Draw();
	void KeyBoard(int key, int scancode, int action, int mods);
	void MouseInput(double xpos, double ypos);
};
