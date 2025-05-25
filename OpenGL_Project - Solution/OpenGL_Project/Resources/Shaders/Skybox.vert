/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Skybox.vert
Description : A vertex shader used for skyboxes.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

layout (location = 0) in vec3 v3fPosition;

uniform mat4 matVP;

out vec3 v3fFragTexCoords;

void main()
{
	vec4 v4fPos = matVP * vec4(v3fPosition, 1.0f);
	gl_Position = v4fPos.xyww;
	v3fFragTexCoords = v3fPosition.xyz;
}