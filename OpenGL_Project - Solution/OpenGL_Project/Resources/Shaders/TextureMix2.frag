#version 460 core

in vec3 v3FragColour;
in vec2 v2FragTexCoords;

uniform sampler2D oTexture2;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = texture(oTexture2, v2FragTexCoords);
}