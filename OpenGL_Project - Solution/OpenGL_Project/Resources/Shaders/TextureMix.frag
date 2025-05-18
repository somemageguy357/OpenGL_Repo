/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : TextureMix.frag
Description : Fragment shader for the mixing of two textures on one shape.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

in vec3 v3fFragColour;
in vec2 v2fFragTexCoords;

uniform float fCurrentTime;

uniform sampler2D oTexture0;
uniform sampler2D oTexture1;

out vec4 v4fFinalColour;

void main()
{
	v4fFinalColour = mix(texture(oTexture0, v2fFragTexCoords), texture(oTexture1, v2fFragTexCoords), ((sin(fCurrentTime) * 0.5f) + 0.5f));
}