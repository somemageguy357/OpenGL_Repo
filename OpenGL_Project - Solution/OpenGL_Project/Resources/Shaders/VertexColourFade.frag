#version 460 core

in vec3 v3FragColour;
uniform float fCurrentTime;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = mix(vec4(v3FragColour, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), ((sin(fCurrentTime) * 0.5f) + 0.5f));
}