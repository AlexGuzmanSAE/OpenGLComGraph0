#pragma once
#include <glad.h>
#include "GLFW/glfw3.h"
#include "string"
#include "map"

class Application
{
	std::map<std::string, GLuint> mapShaders;
	std::map<std::string, GLuint> mapGeometry;
	std::map<std::string, GLint> mapIDVertex;

	void SetUpShaders();
	void SetUpGeometry();
	void SetUpGeometrySingleArray();


	float time{0.0f};
	GLuint time_id;

	GLuint colors_id;

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