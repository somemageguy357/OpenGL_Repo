/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Math.cpp
Description : Contains function definitions for Math.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Math.h"

const float CMath::m_kfDegToRad = 0.0174533f;
const float CMath::m_kfRadToDeg = 57.2958f;

glm::vec3 CMath::Normalize(const glm::vec3 _kv3fVector)
{
	float fMag = (float)sqrt(pow(_kv3fVector.x, 2) + pow(_kv3fVector.y, 2) + pow(_kv3fVector.z, 2));

	if (fMag == 0)
	{
		return { 0.0f, 0.0f, 0.0f };
	}

	glm::vec3 v3fNormalizedVector = _kv3fVector / fMag;

	return v3fNormalizedVector;
}

float CMath::Clamp(const float _kfValue, float _fMin, float _fMax)
{
	if (_kfValue > _fMax)
	{
		return _fMax;
	}

	else if (_kfValue < _fMin)
	{
		return _fMin;
	}

	return _kfValue;
}

float CMath::RadToDeg()
{
	return m_kfRadToDeg;
}

float CMath::DegToRad()
{
	return m_kfDegToRad;
}