#version 460 core

out vec4 fragColor;
in vec4 vertColor;
in vec2 texCoord;
uniform sampler2D tex1;
uniform float interVal;

void main()
{
    vec4 tex1M = texture(tex1, texCoord);
	
	fragColor = tex1M;
}

//Nuevo proyecto basado en HeightMap -> BumpMapping;