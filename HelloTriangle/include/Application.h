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
	void SetUpGeometrySingleArray();

	float time{0.0f};
	GLuint time_id;
public:
	void SetUp();
	void Update();
	void Draw();
	void KeyBoard();
};