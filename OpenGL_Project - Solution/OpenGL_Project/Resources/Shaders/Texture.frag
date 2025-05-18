#version 460 core

in vec3 v3fFragColour;
in vec2 v2fFragTexCoords;

uniform sampler2D oTexture0;

out vec4 v4fFinalColour;

void main()
{
	v4fFinalColour = texture(oTexture0, v2fFragTexCoords);
	//v4fFinalColour = texture(oTexture0, v2fFragTexCoords) * vec4(v3fFragColour, 1.0f);
}