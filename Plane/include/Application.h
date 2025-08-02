#pragma once
#include <glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "string"
#include "map"

class Application
{
	std::map<std::string, GLuint> mapShaders;
	std::map<std::string, GLuint> mapGeometry;
	std::map<std::string, GLint> mapUniforms;

	glm::mat4 projection;
	glm::mat4 camera;
	glm::vec3 eye;
	glm::vec3 center;

	void SetUpShaderPassthru();
	void SetUpShaderTransforms();
	void SetUpShaders();
	void SetUpGeometry();
	void SetUpGeometrySingleArray();


	float time{0.0f};

public:
	float r, g, b, a;
	GLFWwindow* window;
	//void check_keyboard( int key, int scancode, int action, int mods);
	//void check_keyboard_2(GLFWwindow* window, int key, int scancode, int action, int mods);
	void SetUp();
	void Update();
	void Draw();
	void KeyBoard(int key, int scancode, int action, int mods);
};