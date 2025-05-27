/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Model.cpp
Description : Contains function definitions for Model.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Model.h"
#include "ModelMesh.h"
#include "Camera.h"
#include "TimeManager.h"
#include "LightingSettings.h"

#include <iostream>

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _uiProgram);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition)
	: CObject(_v3fPosition)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _uiProgram);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
	: CObject(_v3fPosition, _v3fRotation)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _uiProgram);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
	: CObject(_v3fPosition, _v3fRotation, _v3fScale)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _uiProgram);
}

CModel::~CModel()
{
	delete m_poMesh;
}

void CModel::Render(CSkybox* _poSkybox, CCamera* _poCamera)
{
	glUseProgram(m_uiProgram);

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the object's textures (if any).
	BindTextures(m_uiProgram);

	glActiveTexture(GL_TEXTURE0 + m_oVecTextureIDs.size());
	glBindTexture(GL_TEXTURE_CUBE_MAP, *_poSkybox->GetTextureID());
	glUniform1i(glGetUniformLocation(m_uiProgram, "oSkyboxTexture"), m_oVecTextureIDs.size());

	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));
	glUniform3fv(glGetUniformLocation(m_uiProgram, "v3fCameraPosition"), 1, glm::value_ptr(*_poCamera->GetTransform()->GetPosition()));

	glUniform1f(glGetUniformLocation(m_uiProgram, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(m_uiProgram, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));

	glUniform1f(glGetUniformLocation(m_uiProgram, "fSpecularStrength"), 0.0f);
	glUniform1f(glGetUniformLocation(m_uiProgram, "fObjectShineValue"), 32.0f);

	glDrawArrays(GL_TRIANGLES, 0, m_poMesh->GetTriIndices()->size());

	glBindVertexArray(0);
	glUseProgram(0);
}

void CModel::ModelSetup(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram)
{
	m_poMesh = new CModelMesh(_sModelFilePath);

	for (size_t i = 0; i < _oVecTextureFilePaths.size(); i++)
	{
		AddTexture(_oVecTextureFilePaths[i]);
	}

	m_uiProgram = _uiProgram;
}