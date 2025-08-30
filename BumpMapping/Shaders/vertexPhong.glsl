#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoord;

uniform float time;
uniform float uniFrecuency;
uniform float amplitude;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 accumTrans;


out mat4 fragCamera;
out mat4 fragAccum;

out vec4 vertexPos;

uniform vec4 colorPos;
out vec4 fragPosition;


// Light Vars
out vec4 lightColor;
out vec2 texCoord;



void main()
{
	fragPosition = vPosition;
	
	fragCamera = camera;
	fragAccum = accumTrans;

	texCoord = vTextCoord;

	gl_Position = projection * camera * accumTrans * vPosition;  //equivale a hacer return gl_Position
}

