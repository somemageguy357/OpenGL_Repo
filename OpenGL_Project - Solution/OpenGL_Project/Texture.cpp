#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

CTexture::CTexture(std::string _sFilePath)
{
	stbi_set_flip_vertically_on_load(true);

	int iImageWidth;
	int iImageHeight;
	int iImageComponents;
	unsigned char* pucImageData = stbi_load(_sFilePath.c_str(), &iImageWidth, &iImageHeight, &iImageComponents, 0);

	//Create and bind a new texture variable.
	glGenTextures(1, &uiTexture);
	glBindTexture(GL_TEXTURE_2D, uiTexture);

	//Check how many components the loaded image has (RGBA or RGB).
	GLint uiLoadedComponents = GL_RGBA;

	if (iImageComponents != 4)
	{
		uiLoadedComponents = GL_RGB;
	}

	//Populate the texture with image data.
	glTexImage2D(GL_TEXTURE_2D, 0, uiLoadedComponents, iImageWidth, iImageHeight, 0, uiLoadedComponents, GL_UNSIGNED_BYTE, pucImageData);

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

GLuint CTexture::GetTexture()
{
	return uiTexture;
}