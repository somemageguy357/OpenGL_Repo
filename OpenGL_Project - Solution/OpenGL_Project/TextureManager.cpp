#include "TextureManager.h"

#include <iostream>

std::vector<CTextureManager::TTextureIDMap*> CTextureManager::m_oVecTextureIDMaps;

GLuint CTextureManager::CreateTexture(std::string _sFilePath)
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

	CTexture newTexture = CTexture(_sFilePath);
	m_oVecTextureIDMaps.push_back(new TTextureIDMap(_sFilePath, newTexture.GetTextureID()));

	return newTexture.GetTextureID();
}

void CTextureManager::DestroyTextures()
{
	for (size_t i = 0; i < m_oVecTextureIDMaps.size(); i++)
	{
		delete m_oVecTextureIDMaps[i];
	}
}