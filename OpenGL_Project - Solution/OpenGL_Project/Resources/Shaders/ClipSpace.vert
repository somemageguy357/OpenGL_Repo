/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ClipSpace.vert
Description : Vertex shader for camera-relative rendering.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

layout (location = 0) in vec3 v3Position;
layout (location = 1) in vec3 v3Colour;
layout (location = 2) in vec2 v2TexCoords;

uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;

out vec3 v3FragColour;
out vec2 v2FragTexCoords;

void main()
{
	gl_Position = matProjection * matView * matModel * vec4(v3Position, 1.0f);
	v3FragColour = v3Colour;
	v2FragTexCoords = v2TexCoords;
}