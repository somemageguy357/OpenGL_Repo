/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Mesh.cpp
Description : Contains function definitions for Mesh.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Mesh.h"
#include "TimeManager.h"
#include "LightingSettings.h"

#include <iostream>

std::vector<CMesh::InstancedVAO> CMesh::m_oVecInstancedVAOs;

CMesh::CMesh() {}

CMesh::~CMesh() {}

bool CMesh::GetExistingVAOInstance(std::string _sFilePath, GLuint* _puiVAO, int* _piInstanceCount)
{
	for (size_t i = 0; i < m_oVecInstancedVAOs.size(); i++)
	{
		if (m_oVecInstancedVAOs[i].sFilePath == _sFilePath)
		{
			std::cout << "Existing VAO found. Setting return values.\n";
			m_oVecInstancedVAOs[i].iInstanceCount += 1;
			*_puiVAO = m_oVecInstancedVAOs[i].uiVAO;
			*_piInstanceCount = m_oVecInstancedVAOs[i].iInstanceCount;
			return true;
		}
	}

	std::cout << "No existing VAO found.\n";
	return false;

}

void CMesh::AddVAOInstance(std::string _sFilePath, GLuint _uiVAO)
{
	m_oVecInstancedVAOs.push_back(InstancedVAO(_sFilePath, _uiVAO));
}

int CMesh::GetInstanceCount(GLuint _uiVAO)
{
	for (size_t i = 0; i < m_oVecInstancedVAOs.size(); i++)
	{
		if (m_oVecInstancedVAOs[i].uiVAO == _uiVAO)
		{
			return m_oVecInstancedVAOs[i].iInstanceCount;
		}
	}

	return 0;
}

void CMesh::Render(ShaderLoader::ShaderProgram* _poProgram, CCamera* _poCamera, CSkybox* _poSkybox, int _iTextureCount)
{

}

GLuint* CMesh::GetVAO()
{
	return &m_uiVAO;
}

std::vector<float>* CMesh::GetVertexData()
{
	return &m_oVecVertexData;
}

std::vector<unsigned int>* CMesh::GetTriIndices()
{
	return &m_oVecTriIndices;
}

void CMesh::RenderModel(ShaderLoader::ShaderProgram* _poProgram, CCamera* _poCamera)
{
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));

	glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "v3fCameraPosition"), 1, glm::value_ptr(*_poCamera->GetTransform()->GetPosition()));
}

void CMesh::RenderLighting(ShaderLoader::ShaderProgram* _poProgram)
{
	//Ambient Lighting
	glUniform1f(glGetUniformLocation(_poProgram->uiID, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(_poProgram->uiID, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));
	glUniform1f(glGetUniformLocation(_poProgram->uiID, "fObjectShineValue"), 32.0f);

	#pragma region PointLighting
	glUniform1i(glGetUniformLocation(_poProgram->uiID, "bPointLightsEnabled"), CLightingSettings::GetPointLightsEnabled());

	if (CLightingSettings::GetPointLightsEnabled() == true)
	{
		std::vector<CLightingSettings::PointLight*>* poVecPointLightPtrs = CLightingSettings::GetPointLights();
		std::string sUniform = "";

		for (size_t i = 0; i < CLightingSettings::GetPointLightCount(); i++)
		{
			sUniform = "oPointLights[" + std::to_string(i) + "].v3fPosition";
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), 1, glm::value_ptr((*poVecPointLightPtrs)[i]->v3fPosition));

			sUniform = "oPointLights[" + std::to_string(i) + "].v3fColour";
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), 1, glm::value_ptr((*poVecPointLightPtrs)[i]->v3fColour));

			sUniform = "oPointLights[" + std::to_string(i) + "].fSpecularStrength";
			glUniform1f(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fSpecularStrength);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationConstant";
			glUniform1f(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationConstant);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationLinear";
			glUniform1f(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationLinear);

			sUniform = "oPointLights[" + std::to_string(i) + "].fAttenuationExponent";
			glUniform1f(glGetUniformLocation(_poProgram->uiID, sUniform.c_str()), (*poVecPointLightPtrs)[i]->fAttenuationExponent);
		}

		glUniform1ui(glGetUniformLocation(_poProgram->uiID, "uiPointLightCount"), CLightingSettings::GetPointLightCount());
	}
	#pragma endregion

	#pragma region DirectionalLighting
	glUniform1i(glGetUniformLocation(_poProgram->uiID, "bDirectionalLightsEnabled"), CLightingSettings::GetDirectionalLightsEnabled());

	if (CLightingSettings::GetDirectionalLightsEnabled() == true)
	{
		CLightingSettings::DirectionalLight* poDirectionalLight = CLightingSettings::GetDirectionalLight();

		if (poDirectionalLight != nullptr)
		{
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, "oDirectionalLight.v3fDirection"), 1, glm::value_ptr(poDirectionalLight->v3fDirection));
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, "oDirectionalLight.v3fColour"), 1, glm::value_ptr(poDirectionalLight->v3fColour));
			glUniform1f(glGetUniformLocation(_poProgram->uiID, "oDirectionalLight.fSpecularStrength"), poDirectionalLight->fSpecularStrength);
		}
	}
	#pragma endregion

	#pragma region SpotLighting
	glUniform1i(glGetUniformLocation(_poProgram->uiID, "bSpotLightsEnabled"), CLightingSettings::GetSpotLightsEnabled());

	if (CLightingSettings::GetSpotLightsEnabled() == true)
	{
		CLightingSettings::SpotLight* poSpotLight = CLightingSettings::GetSpotLight();

		if (poSpotLight != nullptr)
		{
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, "oSpotLight.v3fPosition"), 1, glm::value_ptr(poSpotLight->v3fPosition));
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, "oSpotLight.v3fDirection"), 1, glm::value_ptr(poSpotLight->v3fDirection));
			glUniform3fv(glGetUniformLocation(_poProgram->uiID, "oSpotLight.v3fColour"), 1, glm::value_ptr(poSpotLight->v3fColour));
			glUniform1f(glGetUniformLocation(_poProgram->uiID, "oSpotLight.fSpecularStrength"), poSpotLight->fSpecularStrength);
			glUniform1f(glGetUniformLocation(_poProgram->uiID, "oSpotLight.fInnerConeAngle"), poSpotLight->fInnerConeAngle);
			glUniform1f(glGetUniformLocation(_poProgram->uiID, "oSpotLight.fOuterConeAngle"), poSpotLight->fOuterConeAngle);
		}
	}
	#pragma endregion
}

void CMesh::RenderReflections(ShaderLoader::ShaderProgram* _poProgram, CSkybox* _poSkybox, int _iTextureCount)
{
	glActiveTexture(GL_TEXTURE0 + _iTextureCount);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *_poSkybox->GetTextureID());
	glUniform1i(glGetUniformLocation(_poProgram->uiID, "oSkyboxTexture"), _iTextureCount);
}