/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Skybox.h
Description : An object representing a skybox.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Camera.h"
#include "SkyboxMesh.h"

class CSkybox
{
public:
	CSkybox() = delete;
	CSkybox(GLuint _uiProgram, std::vector<std::string> _oVecImageFilePaths);
	~CSkybox();

	void Render(CCamera* _poCamera);

	GLuint* GetTextureID();

private:
	CMesh* m_poMesh = nullptr;

	GLuint m_uiProgram = 0;
	GLuint m_uiTextureID = 0;

	void CreateTextures(std::vector<std::string> _oVecImageFilePaths);
};