#version 460 core

in vec3 FragColour;

out vec4 FinalColour;

void main()
{
	FinalColour = vec4(FragColour, 1.0f);
}