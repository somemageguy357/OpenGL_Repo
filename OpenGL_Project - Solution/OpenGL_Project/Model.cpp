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

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _poProgram, _v3fColour);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition)
	: CObject(_v3fPosition)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _poProgram, _v3fColour);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
	: CObject(_v3fPosition, _v3fRotation)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _poProgram, _v3fColour);
}

CModel::CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
	: CObject(_v3fPosition, _v3fRotation, _v3fScale)
{
	ModelSetup(_sModelFilePath, _oVecTextureFilePaths, _poProgram, _v3fColour);
}

CModel::~CModel()
{
	delete m_poMesh;
}

void CModel::Render(CSkybox* _poSkybox, CCamera* _poCamera)
{
	glUseProgram(m_poProgram->uiID);

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the object's textures (if any).
	BindTextures(m_poProgram->uiID);

	RenderModel(_poCamera);

	if (m_poProgram->bRenderLighting == true)
	{
		RenderLighting();
	}

	if (m_poProgram->bRenderReflections == true)
	{
		RenderReflections(_poSkybox);
	}

	glDrawArraysInstanced(GL_TRIANGLES, 0, m_poMesh->GetTriIndices()->size(), m_poMesh->GetInstanceCount(*m_poMesh->GetVAO()));

	glBindVertexArray(0);
	glUseProgram(0);
}

void CModel::ModelSetup(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour)
{
	m_poMesh = new CModelMesh(_sModelFilePath, _v3fColour);

	for (size_t i = 0; i < _oVecTextureFilePaths.size(); i++)
	{
		AddTexture(_oVecTextureFilePaths[i]);
	}

	m_poProgram = _poProgram;
}

void CModel::RenderModel(CCamera* _poCamera)
{
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));

	glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "v3fCameraPosition"), 1, glm::value_ptr(*_poCamera->GetTransform()->GetPosition()));
}

void CModel::RenderLighting()
{
	//Ambient Lighting
	glUniform1f(glGetUniformLocation(m_poProgram->uiID, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));
	glUniform1f(glGetUniformLocation(m_poProgram->uiID, "fObjectShineValue"), 32.0f);

	#pragma region PointLighting
	glUniform1i(glGetUniformLocation(m_poProgram->uiID, "bPointLightsEnabled"), CLightingSettings::GetPointLightsEnabled());

	if (CLightingSettings::GetPointLightsEnabled() == true)
	{
		std::vector<CLightingSettings::PointLight*>* poVecPointLightPtrs = CLightingSettings::GetPointLights();
		std::string sUniform = "";

		for (size_t i = 0; i < CLightingSettings::GetPointLightCount(); i++)
		{
			sUniform = "oPointLights[" + std::to_string(i) + "].v3fPosition";
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), 1, glm::value_ptr((*poVecPointLightPtrs)[i]->v3fPosition));

			sUniform = "oPointLights[" + std::to_string(i) + "].v3fColour";
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), 1, glm::value_ptr((*poVecPointLightPtrs)[i]->v3fColour));

			sUniform = "oPointLights[" + std::to_string(i) + "].fSpecularStrength";
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fSpecularStrength);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationConstant";
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationConstant);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationLinear";
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationLinear);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationExponent";
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationExponent);
		}

		glUniform1ui(glGetUniformLocation(m_poProgram->uiID, "uiPointLightCount"), CLightingSettings::GetPointLightCount());
	}
	#pragma endregion

	#pragma region DirectionalLighting
	glUniform1i(glGetUniformLocation(m_poProgram->uiID, "bDirectionalLightsEnabled"), CLightingSettings::GetDirectionalLightsEnabled());

	if (CLightingSettings::GetDirectionalLightsEnabled() == true)
	{
		CLightingSettings::DirectionalLight* poDirectionalLight = CLightingSettings::GetDirectionalLight();

		if (poDirectionalLight != nullptr)
		{
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "oDirectionalLight.v3fDirection"), 1, glm::value_ptr(poDirectionalLight->v3fDirection));
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "oDirectionalLight.v3fColour"), 1, glm::value_ptr(poDirectionalLight->v3fColour));
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, "oDirectionalLight.fSpecularStrength"), poDirectionalLight->fSpecularStrength);
		}
	}
	#pragma endregion

	#pragma region SpotLighting
	glUniform1i(glGetUniformLocation(m_poProgram->uiID, "bSpotLightsEnabled"), CLightingSettings::GetSpotLightsEnabled());

	if (CLightingSettings::GetSpotLightsEnabled() == true)
	{
		CLightingSettings::SpotLight* poSpotLight = CLightingSettings::GetSpotLight();

		if (poSpotLight != nullptr)
		{
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.v3fPosition"), 1, glm::value_ptr(poSpotLight->v3fPosition));
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.v3fDirection"), 1, glm::value_ptr(poSpotLight->v3fDirection));
			glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.v3fColour"), 1, glm::value_ptr(poSpotLight->v3fColour));
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.fSpecularStrength"), poSpotLight->fSpecularStrength);
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.fInnerConeAngle"), poSpotLight->fInnerConeAngle);
			glUniform1f(glGetUniformLocation(m_poProgram->uiID, "oSpotLight.fOuterConeAngle"), poSpotLight->fOuterConeAngle);
		}
	}
	#pragma endregion
}

void CModel::RenderReflections(CSkybox* _poSkybox)
{
	glActiveTexture(GL_TEXTURE0 + m_oVecTextureIDs.size());
	glBindTexture(GL_TEXTURE_CUBE_MAP, *_poSkybox->GetTextureID());
	glUniform1i(glGetUniformLocation(m_poProgram->uiID, "oSkyboxTexture"), m_oVecTextureIDs.size());
}
