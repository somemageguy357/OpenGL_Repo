#version 460 core

uniform samplerCube oTextureSkybox;

in vec3 v3fFragTexCoords;

out vec4 v4fFinalColour;

void main()
{
	v4fFinalColour = texture(oTextureSkybox, v3fFragTexCoords);
}