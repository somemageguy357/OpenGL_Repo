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

layout (location = 0) in vec3 v3fPosition;
layout (location = 1) in vec3 v3fColour;
layout (location = 2) in vec2 v2fTexCoords;
layout (location = 3) in vec3 v3fNormals;

uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;

out vec3 v3fFragColour;
out vec2 v2fFragTexCoords;
out vec3 v3fFragNormals;
out vec3 v3fFragPosition;

void main()
{
	gl_Position = matProjection * matView * matModel * vec4(v3fPosition, 1.0f);
	v3fFragColour = v3fColour;
	v2fFragTexCoords = v2fTexCoords;
	v3fFragNormals = mat3(transpose(inverse(matModel))) * v3fNormals;
	v3fFragPosition = vec3(matModel * vec4(v3fPosition, 1.0f));
}