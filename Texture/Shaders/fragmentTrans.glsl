#version 460 core

out vec4 fragColor;
in vec4 vertColor;
in vec2 texCoord;
uniform sampler2D tex0;

//.rgba * newColorPress.rgba;

void main()
{
	vec4 texelColor = texture(tex0, texCoord);
	fragColor = texelColor;
}
