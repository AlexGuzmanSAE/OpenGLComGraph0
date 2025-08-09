#version 460 core

layout(location = 0) in vec4 vPosition;

uniform float time;
uniform float frecuence;
uniform float amplitude;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;

uniform vec4 colorPos;
out vec4 vertColor;

// Light Vars
out vec4 lightColor;

float F(float x, float z, float frecuence, float time)
{
	//amplitud * (sin(fase + frecuencia * (parametro variable)))
	return cos(time + frecuence * (x * x + z * z));
}

float height(float x, float z, float amplitude, float frecuence, float time)
{
	return amplitude * F(x, z, frecuence, time);
}

struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

vec4 Ambient(Light L, Material M)
{
	return L.ambient * M.ambient;
}

vec4 Diffuse(Light L, Material M, vec3 N)
{
	float maxVal = max(0.0f, dot(normalize(L.position), normalize(N)));

	if (maxVal < 0.0f)
	{
		//Debug
	}

	return L.diffuse * M.diffuse * maxVal;
}

//vec4 Specular(Light L, Material M)
//{
//	return L.specular * M.specular * (R * E) * sh;
//}

void main()
{
	vec3 N = vec3(0.0, cos(radians(45)), sin(radians(45)));

	Light light;
	light.ambient = vec4(0.1f, 1.0f, 0.1f, 1.0f);
	light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
	light.position = vec3(0.0f, 2.0f, 0.3f);

	Material mat;
	mat.ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.diffuse = vec4(0.1f, 0.5f, 1.0f, 1.0f);

	lightColor = Ambient(light, mat) + Diffuse(light, mat, N);
	vec4 newPosition = vPosition;

	//newPosition.y = height(newPosition.x, newPosition.z, amplitude, frecuence, time);
	//
	///*
	//* color = vec4(clamp(0.7 * F(newPosition.x, newPosition.x, amplitude, time, frecuence, 0.3, 0.3, 1.0)));
	//*/

	//if (distance(vec4(0.0f, 0.0f, 0.0f, 1.0f), newPosition) > 0.5f)
	//{
	//	vertColor = colorPos;
	//}
	//else
	//{
	//	vertColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//}

	gl_Position = projection * 
				  camera * 
				  accumTrans * 
				  newPosition;  //equivale a hacer return gl_Position
}

