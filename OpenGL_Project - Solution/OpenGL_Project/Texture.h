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
#include <vector>

//Holds the data of a texture used for rendering to a shape.
class CTexture
{
public:
	CTexture() = delete;

	/// <summary>
	/// Creates a texture using the image file from the given file path. Vertically flips the texture, generates and binds it, smoothes
	/// the edges, generates the mipmaps, and finally unbinds the texture.
	/// </summary>
	/// <param name="_sFilePath:">The file path of the texture.</param>
	CTexture(std::string _sFilePath);

	/// <summary>
	/// Creates an animated texture using the image file from the given file path. Vertically flips the texture, generates and binds it, smoothes
	/// the edges, generates the mipmaps, and finally unbinds the texture.
	/// </summary>
	/// <param name="_sFilePath:">The file path of the texture.</param>
	/// <param name="_iFrames:">The number of frames in the spritesheet.</param>
	/// <param name="_iRows:">The number of rows in the spritesheet.</param>
	/// <param name="_iColumns:">The number of columns in the spritesheet.</param>
	/// <param name="_iFrameRate:">The frame rate of the animation.</param>
	CTexture(std::string _sFilePath, int _iFrames, int _iRows, int _iColumns, int _iFrameRate);

	~CTexture();

	/// <summary>
	/// Returns the GLuint representing the texture.
	/// </summary>
	/// <returns>The GLuint representing the texture./returns>
	GLuint GetTexture();

	/// <summary>
	/// Returns if the texture is an animated texture.
	/// </summary>
	/// <returns>True if animated, false if not.</returns>
	bool GetAnimated();

	/// <summary>
	/// Reduces the current 'cooldown' of the frame change and returns true if the current frame is ready to be changed.
	/// </summary>
	/// <returns>True if the current frame is ready to change, false if not.</returns>
	bool GetNextFrameReady();

	std::vector<float>* GetCurrentFrameTexCoords();

private:
	//The GLuint representing the texture.
	GLuint uiTexture = 0;

	//---ANIMATED ONLY VALUES---
	//The texture is animated?
	bool m_bIsAnimated = false;

	//Vector holding the texture coordinates of the current frame.
	std::vector<float> m_oVecCurrentFrameTexCoords = std::vector<float>(8);

	int m_iCurrentFrame = 0;
	int m_iTotalFrames = 0;
	int m_iFrameRate = 0;
	float m_fCurrentFrameDuration = 0.0f;
	int m_iSpritesheetRows = 0;
	int m_iSpritesheetColumns = 0;
	float m_fFrameTexCoordWidth = 0.0f;
	float m_fFrameTexCoordHeight = 0.0f;
};