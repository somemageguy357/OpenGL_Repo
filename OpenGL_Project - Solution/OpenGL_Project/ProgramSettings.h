/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ProgramSettings.h
Description : Static class containing settings for the program, such as wireframe mode, enabling face culling, etc.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

//Static class containing settings for the program, such as wireframe mode, enabling face culling, etc.
class CProgramSettings
{
public:
	/// <summary>
	/// Checks for key inputs that are used to enable/disable certain settings.
	/// </summary>
	static void Update();

	/// <summary>
	/// Enables or disables wireframe mode.
	/// </summary>
	/// <param name="_bOn:">Enables wireframe mode if true.</param>
	static void SetWireframe(bool _bOn);

	/// <summary>
	/// Enables or disables face culling.
	/// </summary>
	/// <param name="_bOn:">Enables face culling if true.</param>
	static void SetFaceCulling(bool _bOn);

	/// <summary>
	/// Enables or disables depth testing.
	/// </summary>
	/// <param name="_bOn:">Enables depth testing if true.</param>
	static void SetDepthTesting(bool _bOn);

	/// <summary>
	/// Enables or disables texture blending.
	/// </summary>
	/// <param name="_bOn:">Enables texture blending if true.</param>
	static void SetTextureBlending(bool _bOn);

private:
	//Settings values.
	static bool m_bWireframeOn;
	static bool m_bFaceCullingOn;
	static bool m_bDepthTestingOn;
	static bool m_bTextureBlendingOn;

	CProgramSettings() {};
	~CProgramSettings() {};

	//Toggles wireframe mode on/off.
	static void ToggleWireframe();

	//Toggles face culling on/off.
	static void ToggleFaceCulling();
};