#pragma once
#include "Camera.h"
#include "SkyboxMesh.h"

class CSkybox
{
public:
	CSkybox() = delete;
	CSkybox(GLuint _uiProgram, std::vector<std::string> _oVecImageFilePaths);
	~CSkybox();

	void Render();

	GLuint* GetTextureID();

private:
	CCamera* m_poCamera = nullptr;
	CMesh* m_poMesh = nullptr;

	GLuint m_uiProgram = 0;
	GLuint m_uiTextureID = 0;

	void CreateTextures(std::vector<std::string> _oVecImageFilePaths);
};