/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Skybox.cpp
Description : Contains function definitions for Skybox.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Skybox.h"

CSkybox::CSkybox(ShaderLoader::ShaderProgram* _poProgram, std::vector<std::string> _oVecImageFilePaths)
{
	m_poMesh = new CSkyboxMesh("");
	m_poProgram = _poProgram;

	CreateTextures(_oVecImageFilePaths);
}

CSkybox::~CSkybox() {}

void CSkybox::Render(CCamera* _poCamera)
{
	glUseProgram(m_poProgram->uiID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiTextureID);

	glUniform1i(glGetUniformLocation(m_poProgram->uiID, "oTextureSkybox"), 0);

	glm::mat4 matCamViewMatrix = glm::mat4(glm::mat3(*_poCamera->GetViewMatrix()));
	glm::mat4 matCamProjMatrix = *_poCamera->GetProjectionMatrix();

	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matVP"), 1, GL_FALSE, glm::value_ptr(matCamProjMatrix * matCamViewMatrix));

	glBindVertexArray(*m_poMesh->GetVAO());
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_TRIANGLES, m_poMesh->GetTriIndices()->size(), GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}

GLuint* CSkybox::GetTextureID()
{
	return &m_uiTextureID;
}

void CSkybox::CreateTextures(std::vector<std::string> _oVecImageFilePaths)
{
	glGenTextures(1, &m_uiTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiTextureID);
	stbi_set_flip_vertically_on_load(false);

	int iImageWidth;
	int iImageHeight;
	int iImageComponents;

	for (int i = 0; i < 6; i++)
	{
		unsigned char* pucImageData = stbi_load(_oVecImageFilePaths[i].c_str(), &iImageWidth, &iImageHeight, &iImageComponents, 0);

		GLint iLoadedComponents = GL_RGBA;

		if (iImageComponents != 4)
		{
			iLoadedComponents = GL_RGB;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, iLoadedComponents, iImageWidth, iImageHeight, 0, iLoadedComponents, GL_UNSIGNED_BYTE, pucImageData);

		stbi_image_free(pucImageData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}