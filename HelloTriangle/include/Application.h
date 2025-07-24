#pragma once
#include "glad.h"
#include "string"
#include "map"

class Application
{
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	void SetUpShaders();
	void SetUpGeometry();
public:
	void SetUp();
	void Update();
	void Draw();
	void KeyBoard();
};