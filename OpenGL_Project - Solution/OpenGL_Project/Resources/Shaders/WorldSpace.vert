#version 460

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Colour;

uniform mat4 TranslationMatrix;
uniform mat4 RotationMatrix;
uniform mat4 ScaleMatrix;

out vec3 FragColour;

void main()
{
	gl_Position = TranslationMatrix * RotationMatrix * ScaleMatrix * vec4(Position, 1.0f);
	FragColour = Colour;
}