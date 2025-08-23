#version 460 core

out vec4 fragColor;
in vec4 vertColor;
in vec2 texCoord;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float interVal;

//.rgba * newColorPress.rgba;

void main()
{
	vec4 texelColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), interVal);
	fragColor = texelColor;
}
