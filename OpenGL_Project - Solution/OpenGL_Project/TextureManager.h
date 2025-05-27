#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>
#include <vector>

class CTextureManager
{
public:
	/// <summary>
	/// Creates a texture using the given file path and returns its ID. If the texture already exists, it will instead find and return its ID.
	/// </summary>
	/// <param name="_sFilePath:">The file path of the texture.</param>
	/// <returns>The texture's ID.</returns>
	static GLuint GetTexture(std::string _sFilePath);

	static void DestroyTextures();

private:
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

	static GLuint CreateNewTexture(std::string _sFilePath);
};