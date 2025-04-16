/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : WindowManager.h
Description : contains the render window and its properties.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

//Static class that contains the render window and its properties.
class CWindowManager
{
public:
	/// <summary>
	/// Sets the width value of the window.
	/// </summary>
	/// <param name="_iWidth:">The width value of the window.</param>
	static void SetWidth(int _iWidth);

	/// <summary>
	/// Returns the width value of the window.
	/// </summary>
	/// <returns>The width value of the window.</returns>
	static int GetWidth();

	/// <summary>
	/// Sets the height value of the window.
	/// </summary>
	/// <param name="_iHeight:">The height value of the window.</param>
	static void SetHeight(int _iHeight);

	/// <summary>
	/// Returns the height value of the window.
	/// </summary>
	/// <returns>The height value of the window.</returns>
	static int GetHeight();

	/// <summary>
	/// Sets both the width and height values of the window.
	/// </summary>
	/// <param name="_iWidth:">The width value of the window.</param>
	/// <param name="_iHeight:">The height value of the window.</param>
	static void SetSize(int _iWidth, int _iHeight);

	/// <summary>
	/// Sets the pointer to the render window to the given value.
	/// </summary>
	/// <param name="_poWindow:">The render window.</param>
	static void SetWindow(GLFWwindow* _poWindow);

	/// <summary>
	/// Returns a pointer to the render window.
	/// </summary>
	/// <returns>A pointer to the render window.</returns>
	static GLFWwindow* GetWindow();

	/// <summary>
	/// Checks for inputs.
	/// </summary>
	static void Update();

private:
	CWindowManager() {};
	~CWindowManager() {};

	static GLFWwindow* m_poWindow;

	static int m_iWidth;
	static int m_iHeight;
};