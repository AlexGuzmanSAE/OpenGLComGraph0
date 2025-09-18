#version 460 core

layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 vColor;

uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;
uniform float frecuency;
uniform float amplitude;


	float F(float x, float z,float amplitude,float phase, float frecuency)
	{
		return amplitude * cos(phase + frecuency * (x * x + z * z));
	}

	
void main()
{
	vec4 newPosition = vPosition;

	gl_Position = projection * camera *  accumTrans * newPosition;  //equivale a hacer return gl_Position
}