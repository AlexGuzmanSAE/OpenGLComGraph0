#version 460 core

uniform vec4 colorPos;
out vec4 fragColor;

void main()
{
	//.rgba * newColorPress.rgba;
    fragColor = colorPos;
}
