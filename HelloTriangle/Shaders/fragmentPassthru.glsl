#version 460 core

in vec4 color;
out vec4 fragColor;

//Vars del c++
uniform vec4 newColorPress;

void main()
{
	//.rgba * newColorPress.rgba;
	fragColor = color * newColorPress;
}
