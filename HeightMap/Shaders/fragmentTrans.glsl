#version 460 core

out vec4 fragColor;
in vec4 vertColor;
in vec2 texCoord;
in vec4 tex1M;

uniform float interVal;

//.rgba * newColorPress.rgba;

void main()
{
	//vec4 texelColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), interVal);
	fragColor = tex1M;
}
