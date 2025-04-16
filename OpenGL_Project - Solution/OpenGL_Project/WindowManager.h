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

	static void SetWindow(GLFWwindow* _poWindow);

	static GLFWwindow* GetWindow();

	static void Update();

private:
	CWindowManager() {};
	~CWindowManager() {};

	static GLFWwindow* m_poWindow;

	static int m_iWidth;
	static int m_iHeight;
};