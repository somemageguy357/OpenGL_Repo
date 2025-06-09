/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : TextureManager.h
Description : Static class that handles the creation of textures and acts as a container for them.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>
#include <vector>

//Static class that handles the creation of textures and acts as a container for them.
class CTextureManager
{
public:
	/// <summary>
	/// Creates a texture using the given file path and returns its ID. If the texture already exists, it will instead find and return its ID.
	/// </summary>
	/// <param name="_sFilePath:">The file path of the texture.</param>
	/// <returns>The texture's ID.</returns>
	static GLuint GetTexture(std::string _sFilePath);

	/// <summary>
	/// Deletes all textures.
	/// </summary>
	static void DestroyTextures();

private:
	//Contains a texture's ID and the file path string used to load the texture from file.
	struct TTextureIDMap
	{
		std::string sFilePath = "";
		GLuint uiTextureID = 0;

		TTextureIDMap(std::string _sFilePath, GLuint _uiTextureID)
		{
			sFilePath = _sFilePath;
			uiTextureID = _uiTextureID;
		}
	};

	static std::vector<TTextureIDMap*> m_oVecTextureIDMaps;

	CTextureManager() = delete;
	~CTextureManager() = delete;

	/// <summary>
	/// Performs the texture creation process and returns the ID that is generated. Creates and binds the texture ID and 
	/// assigns the texture data to it.
	/// </summary>
	/// <param name="_sFilePath:">The file path of the texture.</param>
	/// <returns>The texture ID.</returns>
	static GLuint CreateNewTexture(std::string _sFilePath);
};