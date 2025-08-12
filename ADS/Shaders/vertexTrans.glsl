#version 460 core

layout(location = 0) in vec4 vPosition;

uniform float time;
uniform float uniFrecuency;
uniform float amplitude;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;

uniform vec4 colorPos;
out vec4 vertColor;

// Light Vars
out vec4 lightColor;

float F(float x, float z, float frecuency, float phase, float amplitude)
{
	//amplitud * (sin(fase + frecuencia * (parametro variable)))
	return amplitude * (cos(phase + frecuency * (x * x + z * z)));
}


float DF(float a, float b, float frecuency, float phase, float amplitude)
{
	return -sin(phase + frecuency * (a * a + b * b) * (2.0 + 2.0 * a));
}

vec3 NormalCalc(float x, float z, float frecuency, float phase, float amplitude)
{
	return normalize(vec3(
	DF(x, z, frecuency, phase, amplitude), 
	1.0, 
	DF(z, x, frecuency, phase, amplitude)
	));
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

vec4 Specular(Light L, Material M, vec3 eye, vec3 vertexPos, vec3 N, float SH )
{
	vec3 view = normalize(eye) - normalize(vertexPos);
	vec3 RE = normalize(reflect((eye - L.position), N));
	vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
	if(dot(L.position, view) > 0.0)
	{
		specular =  L.specular * M.specular * pow(max(0.0, dot(view, RE)), SH);
	}
	return specular;
}

void main()
{
	vec3 N = vec3(0.0, 0.1,0.0);

	Light light;
	light.ambient = vec4(0.1f, 1.0f, 0.1f, 1.0f);
	light.diffuse = vec4(1.0f, 0.1f, 1.0f, 1.0f);
	light.position = vec3(0.0f, 2.0f, 0.3f);
	light.specular = vec4(0.0, 0.5, 0.0, 1.0);

	Material mat;
	mat.ambient = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	mat.diffuse = vec4(0.1f, 0.5f, 1.0f, 1.0f);
	mat.specular = vec4(0.0, 0.5, 0.0, 1.0);

	
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
	newPosition.y = F(newPosition.x, newPosition.z, uniFrecuency, time, amplitude); 
	N = NormalCalc(newPosition.x, newPosition.z, uniFrecuency, time, amplitude);
	mat4 matForNormals = transpose(inverse(camera * accumTrans));
	N = normalize(matForNormals * vec4(N, 1.0)).xyz;

	lightColor = Ambient(light, mat) + Diffuse(light, mat, N);
	newPosition = camera * accumTrans * newPosition;

	gl_Position = projection * newPosition;  //equivale a hacer return gl_Position
}

