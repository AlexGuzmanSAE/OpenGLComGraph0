
#include "Application.h"
#include <iostream>
#include "ShaderFuncs.h"
#include <vector>
#include "glm/gtc/type_ptr.hpp"

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
	std::string vertexShader{ loadTextFile("Shaders/vertexTrans.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTrans.glsl") };

	//Cargar programa
	mapShaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "Shaders compilados\n";

	mapUniforms["camera_id"] = glGetUniformLocation(mapShaders["transforms"], "camera");
	mapUniforms["projection_id"] = glGetUniformLocation(mapShaders["transforms"], "projection");
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
		1.0f, 1.0f, -1.0f, 1.0f,   // vertive 3 triang 2
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f,  // vertice 2

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

void Application::SetUp()
{
	SetUpShaders();
	//SetUpGeometry();
	SetUpGeometrySingleArray();

	//inicializar params camara
	eye = glm::vec3(0.0f, 0.0f, 2.0f);
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	projection = glm::perspective(glm::radians(45.0f), (1020.0f/720.0f), 0.1f, 10.0f);

	
}

void Application::Update()
{
	time += 0.0001f;
	// Actualizar center
	center = glm::vec3(cos(time), 0.0f, 1.f);
	// Actualizar eye
	eye = glm::vec3(0.0f, 0.0f, 2.5f + cos(time));
	// Actualizar camara
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Draw()
{
	// Seleccionamos programa
	glUseProgram(mapShaders["transforms"]);
	
	glUniform1f(mapUniforms["time_id"], time);
	glUniform4f(mapUniforms["colors_id"], r, g, b, a);
	glUniformMatrix4fv(mapUniforms["camera_id"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(mapUniforms["projection_id"], 1, GL_FALSE, glm::value_ptr(projection));

	// Seleccionar la geometría (del triangulo)
	glBindVertexArray(mapGeometry["triangulo"]);

	// glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Application::KeyBoard(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "P" << std::endl;
		//cambiar colores
		r = 0.5f;
		g = 1.0f;
		b = 0.5f;
		a = 1.0f;
	}
	else if (key == GLFW_KEY_P && action == GLFW_RELEASE)
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}
	else if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		r = 2.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}
	else if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		r = 1.0f;
		g = 2.0f;
		b = 1.0f;
		a = 1.0f;
	}
	else if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		r = 1.0f;
		g = 0.0f;
		b = 2.0f;
		a = 1.0f;
	}
}
