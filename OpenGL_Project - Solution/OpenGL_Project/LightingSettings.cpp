#include "LightingSettings.h"
#include "Math.h"

float CLightingSettings::m_fAmbientStrength = 0.05f;
glm::vec3 CLightingSettings::m_v3fAmbientColour = { 1.0f, 1.0f, 1.0f };

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