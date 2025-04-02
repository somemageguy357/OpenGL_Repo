#version 460 core

in vec3 v3FragColour;
in vec2 v2FragTexCoords;

uniform float fCurrentTime;

uniform sampler2D oTexture0;
uniform sampler2D oTexture1;

out vec4 v4FinalColour;

void main()
{
	v4FinalColour = mix(texture(oTexture0, v2FragTexCoords), texture(oTexture1, v2FragTexCoords), ((sin(fCurrentTime) * 0.5f) + 0.5f));
}