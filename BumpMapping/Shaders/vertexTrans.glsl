#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;

// To calculate pixel luminosity
// L = 0.2126R + 0.7152G + 0.0722B;

out vec2 texCoord;
out vec4 tex1M;

uniform float time;
uniform float frecuence;
uniform float amplitude;

uniform sampler2D tex0;


uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;

uniform vec4 colorPos;
out vec4 vertColor;

vec4 texHeighted;
float resultedLum;

float Luminosity(vec4 colors)
{
	return 0.2126 * colors.r + 0.7152 * colors.g + 0.0722 * colors.b;
}

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
	texCoord = vTextCoord;
	texHeighted = texture(tex0, texCoord);

	newPosition.y = 1.0f * Luminosity(texHeighted);
	

	gl_Position = projection *
				  camera *
				  accumTrans *
				  newPosition;  //equivale a hacer return gl_Position
}

