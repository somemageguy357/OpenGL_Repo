/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Math.h
Description : Static class containing math functions.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

//Static class containing math functions.
class CMath
{
public:
	/// <summary>
	/// Returns a normalized copy of the given vector.
	/// </summary>
	/// <param name="_kv3fVector:">The vector to create a normalized copy of.</param>
	/// <returns>A normalized copy of the given vector.</returns>
	static glm::vec3 Normalize(const glm::vec3 _kv3fVector);

	/// <summary>
	/// Clamps the given value between the min and max values and returns a copy of the result.
	/// </summary>
	/// <param name="_kfValue:">The value to clamp.</param>
	/// <param name="_fMin:">The minimum value to clamp to.</param>
	/// <param name="_fMax:">The maximum value to clamp to.</param>
	/// <returns>A copy of the clamped float value.</returns>
	static float Clamp(const float _kfValue, float _fMin, float _fMax);

	/// <summary>
	/// Multiply a radian value by this to get the degrees equivalent.
	/// </summary>
	/// <returns>57.2958f</returns>
	static float RadToDeg();

	/// <summary>
	/// Multiply a degree value by this to get the radians equivalent.
	/// </summary>
	/// <returns>0.0174533f</returns>
	static float DegToRad();

private:
	CMath() {};
	~CMath() {};

	static const float m_kfRadToDeg;
	static const float m_kfDegToRad;
};