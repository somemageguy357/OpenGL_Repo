/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Skybox.frag
Description : A fragment shader used for skyboxes.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

uniform samplerCube oTextureSkybox;

in vec3 v3fFragTexCoords;

out vec4 v4fFinalColour;

void main()
{
	v4fFinalColour = texture(oTextureSkybox, v3fFragTexCoords);
}