
#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include <vector>
#include "glm/gtc/type_ptr.hpp"
#include "Plane.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "algorithm"

void Application::SetUpShaderPassthru()
{
	//Cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };

	//Cargar programa
	mapShaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "Shaders compilados\n";

	mapUniforms["time_id"] = glGetUniformLocation(mapShaders["passthru"], "time");
	mapUniforms["colors_id"] = glGetUniformLocation(mapShaders["passthru"], "newColorPress");
}

void Application::SetUpShaderTransforms()
{
	//Cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPhong.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTrans.glsl") };

	//Cargar programa
	mapShaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "Shaders compilados\n";

	mapUniforms["camera_id"] = glGetUniformLocation(mapShaders["transforms"], "camera");
	mapUniforms["projection_id"] = glGetUniformLocation(mapShaders["transforms"], "projection");
	mapUniforms["accumTrans_id"] = glGetUniformLocation(mapShaders["transforms"], "accumTrans");
	mapUniforms["time_id"] = glGetUniformLocation(mapShaders["transforms"], "time");
	mapUniforms["interpolateValue"] = glGetUniformLocation(mapShaders["transforms"], "interVal");
	mapUniforms["lightPos"] = glGetUniformLocation(mapShaders["transforms"], "uniPosLight");

	mapUniforms["colors_id"] = glGetUniformLocation(mapShaders["transforms"], "colorPos");
	mapUniforms["amplitude_id"] = glGetUniformLocation(mapShaders["transforms"], "amplitude");
	mapUniforms["frecuence_id"] = glGetUniformLocation(mapShaders["transforms"], "frecuence");
	mapUniforms["rockDiffuse"] = glGetUniformLocation(mapShaders["transforms"], "rockDiffuse");
	mapUniforms["rockNormal"] = glGetUniformLocation(mapShaders["transforms"], "rockNormal");
	mapUniforms["Eye"] = glGetUniformLocation(mapShaders["transforms"], "eye");
}

void Application::SetUpShaders()
{
	SetUpShaderTransforms();
}

void Application::SetUpGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2

		-1.0f, 1.0f, -1.5f, 1.0f,  // vertice 0
		-1.0f, -1.0f, -1.5f, 1.0f, // vertice 2 triang 2
		1.0f, -1.0f, -0.5f, 1.0f,  // vertice 3 triang 2
	};
	
	std::vector<GLfloat> vecTriangleColors
	{
		1.0f, 0.0f, 0.0f, 1.0f,  // RED
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN 
		0.0f, 0.0f, 1.0f, 1.0f,  // BLUE

		1.0f, 0.0f, 0.0f, 1.0f,  // RED
		0.0f, 0.0f, 1.0f, 1.0f,  // BLUE
		1.0f, 1.0f, 1.0f, 1.0f, // GREEN 
	};

	// Crear VertexArrayObject
	GLuint VAO_id, VBO_id;
	GLuint colorVBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	mapGeometry["triangulo"] = VAO_id;

	
	// Crear  TriangleGeometry VertexBufferObject
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), &triangle[0], GL_STATIC_DRAW);

	// Pasar arreglo de vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //geometria
	glEnableVertexAttribArray(0);
	
	// Crear TriangColors VertexBufferObject
	glGenBuffers(1, &colorVBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vecTriangleColors.size(), &vecTriangleColors[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Application::SetUpGeometrySingleArray()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vertice 0
		1.0f, 0.0f, 0.0f, 1.0f,  // RED
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		0.0f, 1.0f, 0.0f, 1.0f,  // GREEN
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2
		0.0f, 0.0f, 1.0f, 1.0f,  // BLUE
	};

	{
		// Crear VertexArrayObject
		GLuint VAO_id, VBO_id;
		

		glGenVertexArrays(1, &VAO_id);
		glBindVertexArray(VAO_id);

		mapGeometry["triangulo"] = VAO_id;


		// Crear  TriangleGeometry VertexBufferObject
		glGenBuffers(1, &VBO_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(),
			&triangle[0], GL_STATIC_DRAW);
	}
	// Pasar arreglo de vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); //geometria
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat))); // colores
	glEnableVertexAttribArray(1);
}

void Application::SetupPlane()
{
	plane.createPlane(1);

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);


	glBufferData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes() + plane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane.getVertexSizeInBytes(), plane.plane);
	glBufferSubData(GL_ARRAY_BUFFER, plane.getVertexSizeInBytes(), plane.getTextureCoordsSizeInBytes(), plane.textureCoords);
	plane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(plane.getVertexSizeInBytes()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

GLuint Application::SetUpTexture(const std::string& filename)
{
	int width, height, channels;
	unsigned char * img = stbi_load(filename.c_str(), &width, &height, &channels, 4);
	if (img == nullptr)
	{
		return -1;
	}

	GLuint texID = -1;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	stbi_image_free(img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

void Application::SetUp()
{
	SetUpShaders();
	SetUpGeometry();
	SetupPlane();
	mapTextures["RockNormals"] = SetUpTexture("Textures/RockNormal.jpg");
	mapTextures["RockDiffuse"] = SetUpTexture("Textures/RockTexture.jpg");
	//SetUpGeometrySingleArray();


	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	//inicializar params camara
	eye = glm::vec3(0.0f, 0.0f, 2.0f);

	center = glm::vec3(0.0f, 0.0f, 0.0f);

	projection = glm::perspective(
				 glm::radians(45.0f), 
				 (1020.0f/720.0f), 0.1f, 200.0f);

	accumTransRotationX = glm::rotate(glm::mat4(1.0f),
		glm::radians(45.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	accumTransRotationY = glm::rotate(glm::mat4(1.0f),
		glm::radians(0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f));

	accumTrans = accumTransRotationX * accumTransRotationY;
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}

void Application::Update()
{
	time += 0.0009f;
	// Actualizar center
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	// Actualizar eye
	eye = glm::vec3(0.0f, 0.0f, 2.0f);

	//Movement rotation
	accumTransRotationX = glm::rotate(glm::mat4(1.0f),
		glm::radians(-eyeXRot),
		glm::vec3(0.0f, 1.0f, 0.0f));

	accumTransRotationY = glm::rotate(glm::mat4(1.0f),
		glm::radians(eyeYRot),
		glm::vec3(1.0f, 0.0f, 0.0f));

	accumTrans = accumTransRotationX * accumTransRotationY;

	// Actualizar camara
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Draw()
{
	// Seleccionamos programa
	glUseProgram(mapShaders["transforms"]);
	
	glUniform1f(mapUniforms["time_id"], time);
	glUniform4f(mapUniforms["colors_id"], r, g, b, a);
	glUniform1f(mapUniforms["amplitude_id"], amplitude);
	glUniform1f(mapUniforms["frecuence_id"], frecuence);
	glUniform1f(mapUniforms["interpolateValue"], interpolateVal);
	glUniform3f(mapUniforms["lightPos"], lightXMove, lightYMove, 0.0f);
	glUniform3f(mapUniforms["Eye"], eye.x, eye.y, eye.z);

	glUniformMatrix4fv(mapUniforms["camera_id"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(mapUniforms["projection_id"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(mapUniforms["accumTrans_id"], 1, GL_FALSE, glm::value_ptr(accumTrans));

	//Seleccionar las texturas
	//texture 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mapTextures["RockDiffuse"]);
	glUniform1i(mapUniforms["rockDiffuse"], 0);
	//Seleccionar las texturas
	//texture 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mapTextures["RockNormals"]);
	glUniform1i(mapUniforms["rockNormal"], 1);


	// Seleccionar la geometría (del triangulo)
	//glBindVertexArray(mapGeometry["triangulo"]);
	glBindVertexArray(plane.vao);

	// glDraw()
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());

}

void Application::KeyBoard(int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		lightYMove += 10.f;
		std::cout << lightYMove << std::endl;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		lightXMove -= 10.f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		lightYMove -= 10.f;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		lightXMove += 10.f;
	}
}

void Application::MouseInput(double xpos, double ypos)
{
	eyeXRot = xpos;
	eyeYRot = ypos;
	
}
