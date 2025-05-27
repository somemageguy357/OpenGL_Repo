/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Cube.cpp
Description : Contains function definitions for Cube.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Cube.h"
#include "CubeMesh.h"
#include "TimeManager.h"
#include "LightingSettings.h"

CCube::CCube() : CObject()
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition) : CObject(_v3fPosition)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CObject(_v3fPosition, _v3fRotation)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CObject(_v3fPosition, _v3fRotation, _v3fScale)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::~CCube() {}

void CCube::Render(CSkybox* _poSkybox, CCamera* _poCamera)
{
	glUseProgram(m_uiProgram);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	//GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the Object's textures (if any).
	BindTextures(m_uiProgram);

	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));
	glUniform3fv(glGetUniformLocation(m_uiProgram, "v3fCameraPosition"), 1, glm::value_ptr(*_poCamera->GetTransform()->GetPosition()));

	glUniform1f(glGetUniformLocation(m_uiProgram, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(m_uiProgram, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));

	glDrawElements(GL_TRIANGLES, m_poMesh->GetTriIndices()->size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}