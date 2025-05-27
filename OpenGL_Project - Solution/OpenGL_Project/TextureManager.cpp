#include "TextureManager.h"
#include <stb_image.h>

#include <iostream>

std::vector<CTextureManager::TTextureIDMap*> CTextureManager::m_oVecTextureIDMaps;

GLuint CTextureManager::GetTexture(std::string _sFilePath)
{
	//Search for an existing texture. Return its ID if it is found.
	for (size_t i = 0; i < m_oVecTextureIDMaps.size(); i++)
	{
		if (m_oVecTextureIDMaps[i]->sFilePath == _sFilePath)
		{
			std::cout << "Found existing texture. Returning its ID.\n";
			return m_oVecTextureIDMaps[i]->uiTextureID;
		}
	}

	//Create a new texture.
	std::cout << "Creating a new texture.\n";

	GLuint uiNewTextureID = CreateNewTexture(_sFilePath);
	m_oVecTextureIDMaps.push_back(new TTextureIDMap(_sFilePath, uiNewTextureID));

	return uiNewTextureID;
}

void CTextureManager::DestroyTextures()
{
	for (size_t i = 0; i < m_oVecTextureIDMaps.size(); i++)
	{
		delete m_oVecTextureIDMaps[i];
	}
}

GLuint CTextureManager::CreateNewTexture(std::string _sFilePath)
{
	GLuint uiTextureID;

	stbi_set_flip_vertically_on_load(true);

	int iImageWidth;
	int iImageHeight;
	int iImageComponents;
	unsigned char* pucImageData = stbi_load(_sFilePath.c_str(), &iImageWidth, &iImageHeight, &iImageComponents, 0);

	//Create and bind a new texture variable.
	glGenTextures(1, &uiTextureID);
	glBindTexture(GL_TEXTURE_2D, uiTextureID);

	//Check how many components the loaded image has (RGBA or RGB).
	GLint iLoadedComponents = GL_RGBA;

	if (iImageComponents != 4)
	{
		iLoadedComponents = GL_RGB;
	}

	//Populate the texture with image data.
	glTexImage2D(GL_TEXTURE_2D, 0, iLoadedComponents, iImageWidth, iImageHeight, 0, iLoadedComponents, GL_UNSIGNED_BYTE, pucImageData);

	//Smooths the edges of a texture by mixing nearby pixels with each other.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Generate the mipmaps, free the memory and unbind the texture.
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pucImageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	return uiTextureID;
}