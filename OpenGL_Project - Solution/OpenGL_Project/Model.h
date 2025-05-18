#pragma once
#include "Shape.h"
#include "Skybox.h"

class CModel : public CShape
{
public:
	CModel(std::string _sFilePath, CSkybox* _poSkybox);
	~CModel();

	void Render(GLuint _uiProgram) override;

private:
	CSkybox* m_poSkybox = nullptr;
};