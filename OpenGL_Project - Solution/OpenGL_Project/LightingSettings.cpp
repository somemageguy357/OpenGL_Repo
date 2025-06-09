/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : LightingSettings.cpp
Description : Contains function definitions for LightingSettings.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "LightingSettings.h"
#include "Math.h"

#include <iostream>

float CLightingSettings::m_fAmbientStrength = 0.05f;
glm::vec3 CLightingSettings::m_v3fAmbientColour = { 1.0f, 1.0f, 1.0f };
const int CLightingSettings::m_kiMaxPointLights = 4;
std::vector<CLightingSettings::PointLight*> CLightingSettings::m_oVecPointLightPtrs(CLightingSettings::m_kiMaxPointLights);
unsigned int CLightingSettings::m_uiPointLightCount;
CLightingSettings::DirectionalLight* CLightingSettings::m_poDirectionalLight = nullptr;
CLightingSettings::SpotLight* CLightingSettings::m_poSpotLight = nullptr;
bool CLightingSettings::m_bPointLightsEnabled = true;
bool CLightingSettings::m_bDirectionalLightsEnabled = true;
bool CLightingSettings::m_bSpotLightsEnabled = true;

void CLightingSettings::SetAmbientStrength(float _fStrength)
{
	m_fAmbientStrength = CMath::Clamp(_fStrength, 0.0f, 1.0f);
}

float CLightingSettings::GetAmbientStrength()
{
	return m_fAmbientStrength;
}

void CLightingSettings::SetAmbientColour(glm::vec3 _v3fColour)
{
	m_v3fAmbientColour = 
	{ 
		CMath::Clamp(_v3fColour.x, 0.0f, 255.0f) / 255.0f,
		CMath::Clamp(_v3fColour.y, 0.0f, 255.0f) / 255.0f,
		CMath::Clamp(_v3fColour.z, 0.0f, 255.0f) / 255.0f
	};
}

void CLightingSettings::SetAmbientColourNormalized(glm::vec3 _v3fColour)
{
	m_v3fAmbientColour =
	{
		CMath::Clamp(_v3fColour.x, 0.0f, 1.0f),
		CMath::Clamp(_v3fColour.y, 0.0f, 1.0f),
		CMath::Clamp(_v3fColour.z, 0.0f, 1.0f)
	};
}

glm::vec3* CLightingSettings::GetAmbientColour()
{
	return &m_v3fAmbientColour;
}

void CLightingSettings::CreatePointLight(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, float _fSpecularStrength, float _fAttConstant, float _fAttLinear, float _fAttExponent)
{
	for (size_t i = 0; i < m_oVecPointLightPtrs.size(); i++)
	{
		if (m_oVecPointLightPtrs[i] == nullptr)
		{
			m_oVecPointLightPtrs[i] = new CLightingSettings::PointLight(_v3fPosition, _v3fColour, _fSpecularStrength, _fAttConstant, _fAttLinear, _fAttExponent);
			m_uiPointLightCount += 1;
			return;
		}
	}

	std::cout << "Cannot create point light: max limit reached. Max: " << m_kiMaxPointLights << std::endl;
}

std::vector<CLightingSettings::PointLight*>* CLightingSettings::GetPointLights()
{
	return &m_oVecPointLightPtrs;
}

unsigned int CLightingSettings::GetPointLightCount()
{
	return m_uiPointLightCount;
}

void CLightingSettings::CreateDirectionalLight(glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength)
{
	if (m_poDirectionalLight != nullptr)
	{
		std::cout << "Replacing existing directional light.\n";
		delete m_poDirectionalLight;
	}

	m_poDirectionalLight = new CLightingSettings::DirectionalLight(_v3fDirection, _v3fColour, _fSpecularStrength);
	m_poDirectionalLight->v3fDirection = CMath::Normalize(m_poDirectionalLight->v3fDirection);
}

CLightingSettings::DirectionalLight * CLightingSettings::GetDirectionalLight()
{
	return m_poDirectionalLight;
}

CLightingSettings::SpotLight* CLightingSettings::CreateSpotLight(glm::vec3 _v3fPosition, glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength, float _fInnerAngle, float _fOuterAngle)
{
	if (m_poSpotLight != nullptr)
	{
		std::cout << "Replacing existing spot light.\n";
		delete m_poSpotLight;
	}

	m_poSpotLight = new CLightingSettings::SpotLight(_v3fPosition, _v3fDirection, _v3fColour, _fSpecularStrength, CMath::DegToRad() * _fInnerAngle, CMath::DegToRad() * _fOuterAngle);
	m_poSpotLight->v3fDirection = CMath::Normalize(m_poSpotLight->v3fDirection);

	return m_poSpotLight;
}

CLightingSettings::SpotLight* CLightingSettings::GetSpotLight()
{
	return m_poSpotLight;
}

void CLightingSettings::DestroyLights()
{
	for (size_t i = 0; i < m_oVecPointLightPtrs.size(); i++)
	{
		delete m_oVecPointLightPtrs[i];
	}

	delete m_poDirectionalLight;
	delete m_poSpotLight;
}

void CLightingSettings::TogglePointLights()
{
	m_bPointLightsEnabled = !m_bPointLightsEnabled;

	for (size_t i = 0; i < m_oVecPointLightPtrs.size(); i++)
	{

	}

	std::cout << "Point Lights Enabled: " << m_bPointLightsEnabled << std::endl;
}

bool CLightingSettings::GetPointLightsEnabled()
{
	return m_bPointLightsEnabled;
}

void CLightingSettings::ToggleDirectionalLights()
{
	m_bDirectionalLightsEnabled = !m_bDirectionalLightsEnabled;
	std::cout << "Directional Lights Enabled: " << m_bDirectionalLightsEnabled << std::endl;
}

bool CLightingSettings::GetDirectionalLightsEnabled()
{
	return m_bDirectionalLightsEnabled;
}

void CLightingSettings::ToggleSpotLights()
{
	m_bSpotLightsEnabled = !m_bSpotLightsEnabled;
	std::cout << "Spot Lights Enabled: " << m_bSpotLightsEnabled << std::endl;
}

bool CLightingSettings::GetSpotLightsEnabled()
{
	return m_bSpotLightsEnabled;
}