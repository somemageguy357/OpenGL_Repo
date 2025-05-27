/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : TimeManager.h
Description : Contains the programs current and delta time values.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>

//Static class that holds the program's current/run time and delta time values.
class CTimeManager
{
public:
	/// <summary>
	/// Returns the program's DeltaTime.
	/// </summary>
	static float GetDeltaTime();

	/// <summary>
	/// Returns the program's CurrentTime.
	/// </summary>
	/// <returns></returns>
	static float GetCurrentTime();

	/// <summary>
	/// Updates the values of DeltaTime and CurrentTime.
	/// </summary>
	static void Update();

private:
	static float m_fDeltaTime;
	static float m_fCurrentTime;

	CTimeManager();
	~CTimeManager();
};