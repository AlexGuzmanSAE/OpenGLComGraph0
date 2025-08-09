#version 460 core

out vec4 fragColor;
in vec4 vertColor;

// Light vars
in vec4 lightColor;

void main()
{
	//.rgba * newColorPress.rgba;
	fragColor = lightColor;
}
