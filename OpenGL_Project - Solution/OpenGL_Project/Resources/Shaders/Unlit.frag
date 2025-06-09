/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Unlit.frag
Description : 



Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

in vec3 v3fFragPosition;
in vec3 v3fFragColour;
in vec2 v2fFragTexCoords;
in vec3 v3fFragNormals;

uniform sampler2D oTexture0;

uniform vec3 v3fCameraPosition;

out vec4 v4fFinalColour;

void main()
{
	v4fFinalColour = vec4(v3fFragColour, 1.0f) * texture(oTexture0, v2fFragTexCoords);
}