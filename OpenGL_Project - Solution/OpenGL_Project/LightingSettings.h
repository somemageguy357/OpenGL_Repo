/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : LightingSettings.h
Description : Static class that holds and controls lighting settings.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glm.hpp>
#include <vector>

//Static class that holds and controls lighting settings.
class CLightingSettings
{
public:
	struct PointLight
	{
		glm::vec3 v3fPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 v3fColour = { 0.0f, 0.0f, 0.0f };
		float fSpecularStrength = 0.0f;

		float fAttenuationConstant = 0.0f;
		float fAttenuationLinear = 0.0f;
		float fAttenuationExponent = 0.0f;

		PointLight() = delete;

		PointLight(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, float _fSpecularStrength, float _fAttConstant, float _fAttLinear, float _fAttExponent)
		{
			v3fPosition = _v3fPosition;
			v3fColour = _v3fColour;
			fSpecularStrength = _fSpecularStrength;
			fAttenuationConstant = _fAttConstant;
			fAttenuationLinear = _fAttLinear;
			fAttenuationExponent = _fAttExponent;
		}
	};

	struct DirectionalLight
	{
		glm::vec3 v3fDirection = { 0.0f, 0.0f, 0.0f };
		glm::vec3 v3fColour = { 0.0f, 0.0f, 0.0f };
		float fSpecularStrength = 0.0f;

		DirectionalLight() = delete;

		DirectionalLight(glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength)
		{
			v3fDirection = _v3fDirection;
			v3fColour = _v3fColour;
			fSpecularStrength = _fSpecularStrength;
		}
	};

	struct SpotLight
	{
		glm::vec3 v3fPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 v3fDirection = { 0.0f, 0.0f, 0.0f };
		glm::vec3 v3fColour = { 0.0f, 0.0f, 0.0f };
		float fSpecularStrength = 0.0f;
		float fInnerConeAngle = 0.0f;
		float fOuterConeAngle = 0.0f;

		SpotLight() = delete;

		SpotLight(glm::vec3 _v3fPosition, glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength, float _fInnerAngle, float _fOuterAngle)
		{
			v3fPosition = _v3fPosition;
			v3fDirection = _v3fDirection;
			v3fColour = _v3fColour;
			fSpecularStrength = _fSpecularStrength;
			fInnerConeAngle = cos(_fInnerAngle);

			if (_fOuterAngle < _fInnerAngle)
			{
				fOuterConeAngle = cos(_fInnerAngle);
			}

			else
			{
				fOuterConeAngle = cos(_fOuterAngle);
			}
		}
	};

	/// <summary>
	/// Sets the strength of the ambient lighting.
	/// </summary>
	/// <param name="_fStrength:">The new strength value.</param>
	static void SetAmbientStrength(float _fStrength);

	/// <summary>
	/// Returns the strength value of the ambient lighting.
	/// </summary>
	/// <returns>The strength value of the ambient lighting.</returns>
	static float GetAmbientStrength();

	/// <summary>
	/// Sets the colour value of ambient lighting.
	/// </summary>
	/// <param name="_v3fColour:">Vector3 containing a colour range of 0-255.</param>
	static void SetAmbientColour(glm::vec3 _v3fColour);

	/// <summary>
	/// Sets the colour value of ambient lighting using normalized values.
	/// </summary>
	/// <param name="_v3fColour:">Vector3 containing a colour range of 0-1.</param>
	static void SetAmbientColourNormalized(glm::vec3 _v3fColour);

	/// <summary>
	/// Returns the normalized colour value of the ambient lighting.
	/// </summary>
	/// <returns>The normalized colour value of the ambient lighting.</returns>
	static glm::vec3* GetAmbientColour();

	static void CreatePointLight(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, float _fSpecularStrength, float _fAttConstant, float _fAttLinear, float _fAttExponent);

	static std::vector<PointLight*>* GetPointLights();

	static unsigned int GetPointLightCount();

	static void CreateDirectionalLight(glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength);

	static DirectionalLight* GetDirectionalLight();

	static SpotLight* CreateSpotLight(glm::vec3 _v3fPosition, glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength, float _fInnerAngle, float _fOuterAngle);

	static SpotLight* GetSpotLight();

	static void DestroyLights();

	static void TogglePointLights();

	static bool GetPointLightsEnabled();

	static void ToggleDirectionalLights();

	static bool GetDirectionalLightsEnabled();

	static void ToggleSpotLights();

	static bool GetSpotLightsEnabled();

private:
	static float m_fAmbientStrength;
	static glm::vec3 m_v3fAmbientColour;

	static const int m_kiMaxPointLights;
	static std::vector<PointLight*> m_oVecPointLightPtrs;
	static unsigned int m_uiPointLightCount;
	static DirectionalLight* m_poDirectionalLight;
	static SpotLight* m_poSpotLight;

	static bool m_bPointLightsEnabled;
	static bool m_bDirectionalLightsEnabled;
	static bool m_bSpotLightsEnabled;

	CLightingSettings() = delete;
	~CLightingSettings() = delete;
};