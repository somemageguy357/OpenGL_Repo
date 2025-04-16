#version 460 core

in vec3 v3FragColour;
in vec2 v2FragTexCoords;

uniform sampler2D oTexture0;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = texture(oTexture0, v2FragTexCoords);
	//v4FinalColour = texture(oTexture0, v2FragTexCoords) * vec4(v3FragColour, 1.0f);
}