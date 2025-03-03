#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Colour;

out vec3 FragColour;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	FragColour = Colour;
}