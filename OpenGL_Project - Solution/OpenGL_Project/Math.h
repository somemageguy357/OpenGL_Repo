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
	static glm::vec3 Normalize(const glm::vec3 _kv3fVector);

	static float Clamp(const float _kfValue, float _fMin, float _fMax);

private:
	CMath() {};
	~CMath() {};
};