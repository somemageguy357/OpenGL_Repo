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
	static glm::vec3 Normalize(const glm::vec3 _v3fVector);

private:
	CMath() {};
	~CMath() {};
};