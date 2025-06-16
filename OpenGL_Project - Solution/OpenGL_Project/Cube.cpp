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
	glUseProgram(m_poProgram->uiID);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	//GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the Object's textures (if any).
	BindTextures(m_poProgram->uiID);

	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));
	glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "v3fCameraPosition"), 1, glm::value_ptr(*_poCamera->GetTransform()->GetPosition()));

	glUniform1f(glGetUniformLocation(m_poProgram->uiID, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(m_poProgram->uiID, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));

	glDrawElements(GL_TRIANGLES, (GLsizei)m_poMesh->GetTriIndices()->size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}