#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include <vector>

void Application::SetUpShaders()
{
	//Cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };

	//Cargar programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "Shaders compilados\n";
}

void Application::SetUpGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2
	};
	//Crear VertexArrayObject
	
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	//crear VertexBufferObject
	
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(), &triangle[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //geometria
	glEnableVertexAttribArray(0);
	
	//Pasar arreglo de vertices
}

void Application::SetUp()
{
	SetUpShaders();
}

void Application::Update()
{
	std::cout << "Application::Update" << std::endl;
}

void Application::Draw()
{
	//std::cout << "Application::Draw" << std::endl;
	
	//Seleccionamos programa
	glUseProgram(shaders["passthru"]);

	//Pasar el resto de los parametros para el programa
	//TODO

	//Seleccionar la geometría (del triangulo)
	glBindVertexArray(geometry["triangulo"]);

	//glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Application::KeyBoard()
{
	std::cout << "Application::KeyBoard" << std::endl;
}
