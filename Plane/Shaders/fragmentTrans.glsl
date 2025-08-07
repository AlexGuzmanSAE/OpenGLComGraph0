#version 460 core

out vec4 fragColor;
in vec4 vertColor;

void main()
{
	//.rgba * newColorPress.rgba;
	fragColor = vertColor;
}
