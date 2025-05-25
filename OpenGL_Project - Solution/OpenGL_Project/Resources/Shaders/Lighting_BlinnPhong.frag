/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Lighting_BlinnPhong.frag
Description : A fragment shader that allows a object's texture to interact with lighting values.
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

uniform float fAmbientStrength;
uniform vec3 v3fAmbientColour;

uniform vec3 v3fLightColour = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 v3fLightPosition = vec3(-1.0f, 1.0f, 0.0f);

uniform float fSpecularStrength;
uniform float fObjectShineValue;

out vec4 v4fFinalColour;

void main()
{
	vec3 v3fAmbient = fAmbientStrength * v3fAmbientColour;

	vec3 v3fNormal = normalize(v3fFragNormals);
	vec3 v3fLightDir = normalize(v3fFragPosition - v3fLightPosition);

	float fDiffuseStrength = max(dot(v3fNormal, -v3fLightDir), 0.0f);
	vec3 v3fDiffuse = fDiffuseStrength * v3fLightColour;

	vec3 v3fReverseViewDir = normalize(v3fCameraPosition - v3fFragPosition);
	vec3 v3fHalfwayVector = normalize(-v3fLightDir + v3fReverseViewDir);
	float fSpecularReflectivity = pow(max(dot(v3fNormal, v3fHalfwayVector), 0.0f), fObjectShineValue);
	vec3 v3fSpecular = fSpecularStrength * fSpecularReflectivity * v3fLightColour;

	vec4 v4fLight = vec4(v3fAmbient + v3fDiffuse + v3fSpecular, 1.0f);

	v4fFinalColour = v4fLight * texture(oTexture0, v2fFragTexCoords);
}