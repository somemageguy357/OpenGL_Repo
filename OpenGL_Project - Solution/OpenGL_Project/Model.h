/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Model.h
Description : An object representing a model created through an obj loader.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

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