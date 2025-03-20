#version 460

layout (location = 0) in vec3 v3Position;
layout (location = 1) in vec3 v3Colour;

uniform mat4 matTranslation;
uniform mat4 matRotation;
uniform mat4 matScale;

out vec3 v3FragColour;

void main()
{
	gl_Position = matTranslation * matRotation * matScale * vec4(v3Position, 1.0f);
	v3FragColour = v3Colour;
}