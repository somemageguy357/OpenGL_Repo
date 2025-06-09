/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Lit.frag
Description : 



Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#version 460 core

#define MAX_POINT_LIGHTS 4

struct PointLight
{
	vec3 v3fPosition;
	vec3 v3fColour;
	float fSpecularStrength;

	float fAttenuationConstant;
	float fAttenuationLinear;
	float fAttenuationExponent;
};

struct DirectionalLight
{
	vec3 v3fDirection;
	vec3 v3fColour;
	float fSpecularStrength;
};

struct SpotLight
{
	vec3 v3fPosition;
	vec3 v3fDirection;
	vec3 v3fColour;
	float fSpecularStrength;
	float fInnerConeAngle;
	float fOuterConeAngle;
};

in vec3 v3fFragPosition;
in vec3 v3fFragColour;
in vec2 v2fFragTexCoords;
in vec3 v3fFragNormals;

uniform sampler2D oTexture0;

uniform vec3 v3fCameraPosition;

uniform float fObjectShineValue;
uniform float fAmbientStrength;
uniform vec3 v3fAmbientColour;

uniform bool bPointLightsEnabled;
uniform bool bDirectionalLightsEnabled;
uniform bool bSpotLightsEnabled;

uniform PointLight oPointLights[MAX_POINT_LIGHTS];
uniform unsigned int uiPointLightCount;
uniform DirectionalLight oDirectionalLight;
uniform SpotLight oSpotLight;

out vec4 v4fFinalColour;

vec3 CalculatePointLights(unsigned int _uiLightIndex);

vec3 CalculateDirectionalLight();

vec3 CalculateSpotLight();

void main()
{
	vec3 v3fAmbient = fAmbientStrength * v3fAmbientColour;

	vec3 v3fTotalLightOutput = vec3(0.0f);

	if (bPointLightsEnabled == true)
	{
		for	(unsigned int i = 0; i < uiPointLightCount; ++i)
		{
			v3fTotalLightOutput += CalculatePointLights(i);
		}
	}

	if (bDirectionalLightsEnabled == true)
	{
		v3fTotalLightOutput += CalculateDirectionalLight();
	}

	if (bSpotLightsEnabled == true)
	{
		v3fTotalLightOutput += CalculateSpotLight();
	}

	v3fTotalLightOutput += v3fAmbient;

	v4fFinalColour = vec4(v3fTotalLightOutput, 1.0f) * texture(oTexture0, v2fFragTexCoords);
}

vec3 CalculatePointLights(unsigned int _uiLightIndex)
{
	vec3 v3fNormal = normalize(v3fFragNormals);
	vec3 v3fLightDir = normalize(v3fFragPosition - oPointLights[_uiLightIndex].v3fPosition);

	float fDiffuseStrength = max(dot(v3fNormal, -v3fLightDir), 0.0f);
	vec3 v3fDiffuse = fDiffuseStrength * oPointLights[_uiLightIndex].v3fColour;

	vec3 v3fReverseViewDir = normalize(v3fCameraPosition - v3fFragPosition);
	vec3 v3fHalfwayVector = normalize(-v3fLightDir + v3fReverseViewDir);
	float fSpecularReflectivity = pow(max(dot(v3fNormal, v3fHalfwayVector), 0.0f), fObjectShineValue);
	vec3 v3fSpecular = oPointLights[_uiLightIndex].fSpecularStrength * fSpecularReflectivity * oPointLights[_uiLightIndex].v3fColour;

	vec3 v3fLight = v3fDiffuse + v3fSpecular;

	float fDistance = length(oPointLights[_uiLightIndex].v3fPosition - v3fFragPosition);
	float fAttenuation = oPointLights[_uiLightIndex].fAttenuationConstant + (oPointLights[_uiLightIndex].fAttenuationLinear * fDistance) +
							(oPointLights[_uiLightIndex].fAttenuationExponent * pow(fDistance, 2.0f));

	v3fLight /= fAttenuation;

	return v3fLight;
}

vec3 CalculateDirectionalLight()
{
	vec3 v3fNormal = normalize(v3fFragNormals);
	vec3 v3fLightDir = normalize(oDirectionalLight.v3fDirection);

	float fDiffuseStrength = max(dot(v3fNormal, -v3fLightDir), 0.0f);
	vec3 v3fDiffuse = fDiffuseStrength * oDirectionalLight.v3fColour;

	vec3 v3fReverseViewDir = normalize(v3fCameraPosition - v3fFragPosition);
	vec3 v3fHalfwayVector = normalize(-v3fLightDir + v3fReverseViewDir);
	float fSpecularReflectivity = pow(max(dot(v3fNormal, v3fHalfwayVector), 0.0f), fObjectShineValue);
	vec3 v3fSpecular = oDirectionalLight.fSpecularStrength * fSpecularReflectivity * oDirectionalLight.v3fColour;

	vec3 v3fLight = v3fDiffuse + v3fSpecular;

	return v3fLight;
}

vec3 CalculateSpotLight()
{
	vec3 v3fNormal = normalize(v3fFragNormals);
	vec3 v3fLightDir = normalize(v3fFragPosition - oSpotLight.v3fPosition);

	float fDot = max(dot(v3fLightDir, oSpotLight.v3fDirection), 0.0f);

	if (fDot > max(oSpotLight.fOuterConeAngle, 0.0f))
	{
		float fDiffuseStrength = max(dot(v3fNormal, -v3fLightDir), 0.0f);
		vec3 v3fDiffuse = fDiffuseStrength * oSpotLight.v3fColour;

		vec3 v3fReverseViewDir = normalize(v3fCameraPosition - v3fFragPosition);
		vec3 v3fHalfwayVector = normalize(-v3fLightDir + v3fReverseViewDir);
		float fSpecularReflectivity = pow(max(dot(v3fNormal, v3fHalfwayVector), 0.0f), fObjectShineValue);
		vec3 v3fSpecular = oSpotLight.fSpecularStrength * fSpecularReflectivity * oSpotLight.v3fColour;

		float fIntensity = clamp((fDot - oSpotLight.fOuterConeAngle) / (oSpotLight.fInnerConeAngle - oSpotLight.fOuterConeAngle), 0.0f, 1.0f);

		vec3 v3fLight = (v3fDiffuse + v3fSpecular) * fIntensity;

		return v3fLight;
	}

	return vec3(0.0f, 0.0f, 0.0f);
}