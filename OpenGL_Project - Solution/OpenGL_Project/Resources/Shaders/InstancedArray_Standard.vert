/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : InstancedArray_Standard.vert
Description : 




Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

layout (location = 0) in vec3 v3fPosition;
layout (location = 1) in vec3 v3fColour;
layout (location = 2) in vec2 v2fTexCoords;
layout (location = 3) in vec3 v3fNormals;
layout (location = 4) in mat4 matInstancedModel;

uniform mat4 matVP;

out vec3 v3fFragPosition;
out vec3 v3fFragColour;
out vec2 v2fFragTexCoords;
out vec3 v3fFragNormals;

void main()
{
	gl_Position = matVP * matInstancedModel * vec4(v3fPosition, 1.0f);

	v3fFragColour = v3fColour;
	v2fFragTexCoords = v2fTexCoords;
	v3fFragNormals = mat3(transpose(inverse(matInstancedModel))) * v3fNormals;
	v3fFragPosition = vec3(matInstancedModel * vec4(v3fPosition, 1.0f));
}