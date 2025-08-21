#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;

out vec2 texCoord;

uniform float time;
uniform float frecuence;
uniform float amplitude;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;

uniform vec4 colorPos;
out vec4 vertColor;

float F(float x, float z, float frecuence, float time)
{
	//amplitud * (sin(fase + frecuencia * (parametro variable)))
	return cos(time + frecuence * (x * x + z * z));
}

float height(float x, float z, float amplitude, float frecuence, float time)
{
	return amplitude * F(x, z, frecuence, time);
}

void main()
{
	vec4 newPosition = vPosition;

	//newPosition.y = height(newPosition.x, newPosition.z, amplitude, frecuence, time);
	
	/*
	* color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuence, 0.3, 0.3, 1.0)));
	*/
	

	if (distance(vec4(0.0f, 0.0f, 0.0f, 1.0f), newPosition) > 0.5f)
	{
		vertColor = colorPos;
	}
	else
	{
		vertColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	texCoord = vTextCoord;
	gl_Position = projection * 
				  camera * 
				  accumTrans * 
				  newPosition;  //equivale a hacer return gl_Position
}

