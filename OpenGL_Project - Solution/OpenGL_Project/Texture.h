/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Texture.h
Description : Holds the data of a texture used for rendering to a shape.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>

//Holds the data of a texture used for rendering to a shape.
class CTexture
{
public:
	CTexture() = delete;

	/// <summary>
	/// Creates a texture using the image file from the given file path. Vertically flips the texture, generates and binds it, smoothes
	/// the edges, generates the mipmaps, and finally unbinds the texture.
	/// </summary>
	/// <param name="_sFilePath:"></param>
	CTexture(std::string _sFilePath);

	~CTexture();

	/// <summary>
	/// Returns the GLuint representing the texture.
	/// </summary>
	/// <returns>The GLuint representing the texture./returns>
	GLuint GetTexture();

private:
	//The GLuint representing the texture.
	GLuint uiTexture = 0;
};