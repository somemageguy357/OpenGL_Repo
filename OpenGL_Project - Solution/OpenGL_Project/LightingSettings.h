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

	/// <summary>
	/// Creates a point light with the given values.
	/// </summary>
	/// <param name="_v3fPosition:">The position of the point light.</param>
	/// <param name="_v3fColour:">The colour of the point light.</param>
	/// <param name="_fSpecularStrength:">The specular strength.</param>
	/// <param name="_fAttConstant:">The attenuation constant value.</param>
	/// <param name="_fAttLinear:">The attenuation linear value.</param>
	/// <param name="_fAttExponent:">The attenuation exponent value.</param>
	static void CreatePointLight(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, float _fSpecularStrength, float _fAttConstant, float _fAttLinear, float _fAttExponent);

	/// <summary>
	/// Gets a pointer to the vector containing all point lights.
	/// </summary>
	/// <returns>A pointer to the vector containing all point lights.</returns>
	static std::vector<PointLight*>* GetPointLights();

	/// <summary>
	/// Gets the number of point lights.
	/// </summary>
	/// <returns>The number of point lights.</returns>
	static unsigned int GetPointLightCount();

	/// <summary>
	/// Creates a directional light with the given values. If a second directional light is created, it will replace the previous one.
	/// </summary>
	/// <param name="_v3fDirection:">The direction of the light.</param>
	/// <param name="_v3fColour:">The colour of the light.</param>
	/// <param name="_fSpecularStrength:">The specular strength.</param>
	static void CreateDirectionalLight(glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength);

	/// <summary>
	/// Gets a pointer to the directional light in the scene.
	/// </summary>
	/// <returns>A pointer to the directional light in the scene.</returns>
	static DirectionalLight* GetDirectionalLight();

	/// <summary>
	/// Creates a spot light with the given values and returns a pointer to it. 
	/// If a second spot light is created, it will replace the previous one.
	/// </summary>
	/// <param name="_v3fPosition:">The position of the spot light.</param>
	/// <param name="_v3fDirection:">The direction of the spot light.</param>
	/// <param name="_v3fColour:">The colour of the spot light.</param>
	/// <param name="_fSpecularStrength:">The specular strength.</param>
	/// <param name="_fInnerAngle:">The inner angle (in degrees).</param>
	/// <param name="_fOuterAngle:">The outer angle (in degress). If this value is less than the inner angle, it is set to the inner angle.</param>
	/// <returns>A pointer to the created spot light.</returns>
	static SpotLight* CreateSpotLight(glm::vec3 _v3fPosition, glm::vec3 _v3fDirection, glm::vec3 _v3fColour, float _fSpecularStrength, float _fInnerAngle, float _fOuterAngle);

	/// <summary>
	/// Gets a pointer to the spot light.
	/// </summary>
	/// <returns>A pointer to the spot light.</returns>
	static SpotLight* GetSpotLight();

	/// <summary>
	/// Deletes all lights in the scene. Called from SceneManager during its DestroyScene() function.
	/// </summary>
	static void DestroyLights();

	/// <summary>
	/// Toggles the boolean representing the on/off state of the point lights.
	/// </summary>
	static void TogglePointLights();

	/// <summary>
	/// Gets the on/off state of the point lights.
	/// </summary>
	/// <returns>The on/off state of the point lights.</returns>
	static bool GetPointLightsEnabled();

	/// <summary>
	/// Toggles the boolean representing the on/off state of the directional light.
	/// </summary>
	static void ToggleDirectionalLights();

	/// <summary>
	/// Gets the on/off state of the directional light.
	/// </summary>
	/// <returns>The on/off state of the directional light.</returns>
	static bool GetDirectionalLightsEnabled();

	/// <summary>
	/// Toggles the boolean representing the on/off state of the spot light.
	/// </summary>
	static void ToggleSpotLights();

	/// <summary>
	/// Gets the on/off state of the spot light.
	/// </summary>
	/// <returns>The on/off state of the spot light.</returns>
	static bool GetSpotLightsEnabled();

private:
	//Ambient lighting values.
	static float m_fAmbientStrength;
	static glm::vec3 m_v3fAmbientColour;

	//Point, Directional, and Spot lights.
	static const int m_kiMaxPointLights;
	static std::vector<PointLight*> m_oVecPointLightPtrs;
	static unsigned int m_uiPointLightCount;
	static DirectionalLight* m_poDirectionalLight;
	static SpotLight* m_poSpotLight;

	//On/off state of the three light types.
	static bool m_bPointLightsEnabled;
	static bool m_bDirectionalLightsEnabled;
	static bool m_bSpotLightsEnabled;

	CLightingSettings() = delete;
	~CLightingSettings() = delete;
};