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

	time_id = glGetUniformLocation(shaders["passthru"], "time");
}

void Application::SetUpGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f,  // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2
	};
	
	std::vector<GLfloat> vecTriangleColors
	{
		1.0f, 0.0f, 0.0f, 1.0f,  // RED
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN 
		0.0f, 0.0f, 1.0f, 1.0f,  // BLUE
	};

	// Crear VertexArrayObject
	GLuint VAO_id, VBO_id;
	GLuint colorVBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	
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
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2

		1.0f, 0.0f, 0.0f, 1.0f,  // RED
		0.0f, 1.0f, 0.0f, 1.0f,  // GREEN
		0.0f, 0.0f, 1.0f, 1.0f,  // BLUE
	};

	{
		// Crear VertexArrayObject
		GLuint VAO_id, VBO_id;

		glGenVertexArrays(1, &VAO_id);
		glBindVertexArray(VAO_id);

		geometry["triangulo"] = VAO_id;


		// Crear  TriangleGeometry VertexBufferObject
		glGenBuffers(1, &VBO_id);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangle.size(),
			&triangle[0], GL_STATIC_DRAW);
	}
	// Pasar arreglo de vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[0]); //geometria
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)&triangle[11]); // colores
	glEnableVertexAttribArray(1);
}

void Application::SetUp()
{
	SetUpShaders();
	SetUpGeometry();
	//SetUpGeometrySingleArray();
}

void Application::Update()
{
	time += 0.0001f;
}

void Application::Draw()
{
	// std::cout << "Application::Draw" << std::endl;
	
	// Seleccionamos programa
	glUseProgram(shaders["passthru"]);

	//Pasar el resto de los parametros para el programa
	// TODO
	glUniform1f(time_id, time);

	// Seleccionar la geometría (del triangulo)
	glBindVertexArray(geometry["triangulo"]);

	// glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Application::KeyBoard()
{
	std::cout << "Application::KeyBoard" << std::endl;
}
