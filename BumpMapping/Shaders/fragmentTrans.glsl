#version 460 core

out vec4 fragColor;
in vec4 lightColor;
in vec2 texCoord;
uniform float interVal;
in vec4 vertexPos;

uniform sampler2D rockNormal;
uniform sampler2D rockDiffuse;
uniform vec3 uniPosLight;
uniform vec3 eye;

in vec4 fragPosition;
in mat4 fragCamera;
in mat4 fragAccum;

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
		return vec4(0.0f);
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
	vec4 neoPosition = fragPosition;
	neoPosition = fragCamera * fragAccum * neoPosition;
	vec4 normal = normalize(texture(rockNormal, texCoord));
	mat4 matForNormals = transpose(inverse(fragCamera * fragAccum));
	vec4 diffuseRock = texture(rockDiffuse, texCoord);

	normal = normalize(matForNormals * normal) ;

	Light light;
	light.ambient = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	light.diffuse = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	light.specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	light.position = uniPosLight;

	Material mat;
	mat.ambient = diffuseRock;
	mat.diffuse = diffuseRock;
	mat.specular = diffuseRock;

	vec4 lightColor = Ambient(light, mat) + 
				 Diffuse(light, mat, normal.xyz) + 
				 Specular(light, mat, eye, neoPosition.xyz, normal.xyz, 8.0);

	fragColor = lightColor;
}