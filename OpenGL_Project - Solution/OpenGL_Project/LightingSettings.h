#pragma once
#include <glm.hpp>

class CLightingSettings
{
public:
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

private:
	static float m_fAmbientStrength;
	static glm::vec3 m_v3fAmbientColour;

	CLightingSettings() = delete;
	~CLightingSettings() = delete;
};