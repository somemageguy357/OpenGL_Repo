#version 460 core

in vec3 FragColour;
uniform float fCurrentTime;

out vec4 FinalColour;

void main()
{
	FinalColour = vec4(FragColour, 1.0f) * abs(sin(fCurrentTime));;
}