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
#include "Object.h"
#include "Skybox.h"

class CModel : public CObject
{
public:
	CModel() = delete;
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram);
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition);
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);
	~CModel();

	void Render(CSkybox* _poSkybox, CCamera* _poCamera) override;

private:
	void ModelSetup(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram);

};