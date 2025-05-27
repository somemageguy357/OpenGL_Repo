/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Texture.cpp
Description : Contains function definitions for Texture.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include "TimeManager.h"

#include <iostream>

CTexture::CTexture(std::string _sFilePath)
{
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
}

CTexture::CTexture(std::string _sFilePath, int _iFrames, int _iRows, int _iColumns, int _iFrameRate)
{
	//Set animation values.
	m_bIsAnimated = true;
	m_iTotalFrames = _iFrames;
	m_iFrameRate = _iFrameRate;
	m_iSpritesheetRows = _iRows;
	m_iSpritesheetColumns = _iColumns;
	m_fCurrentFrameDuration = 1.0f / (float)m_iFrameRate;

	stbi_set_flip_vertically_on_load(true);

	int iImageWidth;
	int iImageHeight;
	int iImageComponents;
	unsigned char* pucImageData = stbi_load(_sFilePath.c_str(), &iImageWidth, &iImageHeight, &iImageComponents, 0);

	//The width and height of each frame of the texture in texture coordinates.
	m_fFrameTexCoordWidth = 1.0f / (float)m_iSpritesheetColumns;
	m_fFrameTexCoordHeight = 1.0f / (float)m_iSpritesheetRows;

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
}

CTexture::~CTexture() {}

GLuint CTexture::GetTextureID()
{
	return uiTextureID;
}

bool CTexture::GetAnimated()
{
	return m_bIsAnimated;
}

bool CTexture::GetNextFrameReady()
{
	//The remaining time left until the next frame of the texture can change.
	if (m_fCurrentFrameDuration > 0.0f)
	{
		m_fCurrentFrameDuration -= CTimeManager::GetDeltaTime();
		return false;
	}

	m_fCurrentFrameDuration = 1.0f / m_iFrameRate;
	return true;
}

std::vector<float>* CTexture::GetCurrentFrameTexCoords()
{
	//The index position of the current frame in the spritesheet.
	int iCurrentFrameX = m_iCurrentFrame % m_iSpritesheetColumns;
	int iCurrentFrameY = m_iCurrentFrame / m_iSpritesheetColumns;

	//Repeats the remainder calc for 3+ rows.
	while (iCurrentFrameX > m_iSpritesheetColumns)
	{
		iCurrentFrameX = m_iCurrentFrame % m_iSpritesheetColumns;
	}

	//TL
	m_oVecCurrentFrameTexCoords[0] = m_fFrameTexCoordWidth * iCurrentFrameX;
	m_oVecCurrentFrameTexCoords[1] = 1.0f - (m_fFrameTexCoordHeight * iCurrentFrameY);

	//TR
	m_oVecCurrentFrameTexCoords[2] = m_fFrameTexCoordWidth * (iCurrentFrameX + 1);
	m_oVecCurrentFrameTexCoords[3] = 1.0f - (m_fFrameTexCoordHeight * iCurrentFrameY);

	//BR
	m_oVecCurrentFrameTexCoords[4] = m_fFrameTexCoordWidth * (iCurrentFrameX + 1);
	m_oVecCurrentFrameTexCoords[5] = 1.0f - (m_fFrameTexCoordHeight * (iCurrentFrameY + 1));

	//BL
	m_oVecCurrentFrameTexCoords[6] = m_fFrameTexCoordWidth * iCurrentFrameX;
	m_oVecCurrentFrameTexCoords[7] = 1.0f - (m_fFrameTexCoordHeight * (iCurrentFrameY + 1));

	//Reset to the first frame if the current frame is the last one in the spritesheet.
	if (m_iCurrentFrame == (m_iTotalFrames - 1))
	{
		m_iCurrentFrame = 0;
	}

	else
	{
		m_iCurrentFrame += 1;
	}

	return &m_oVecCurrentFrameTexCoords;
}