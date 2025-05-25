/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : UI.vert
Description : CURRENTLY UNUSED AND UNFINISHED.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

layout (location = 0) in vec3 v3fPosition;
layout (location = 1) in vec3 v3fColour;
layout (location = 2) in vec2 v2fTexCoords;

uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;

out vec3 v3fFragColour;
out vec2 v2fFragTexCoords;

void main()
{
	gl_Position = matProjection * matView * matModel * vec4(v3fPosition, 1.0f);
	v3fFragColour = v3fColour;
	v2fFragTexCoords = v2fTexCoords;
}