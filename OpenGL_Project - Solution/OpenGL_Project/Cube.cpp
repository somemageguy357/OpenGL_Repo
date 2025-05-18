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
#include "Camera.h"
#include "TimeManager.h"
#include "LightingSettings.h"

CCube::CCube() : CShape()
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition) : CShape(_v3fPosition)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::~CCube() {}

void CCube::Render(GLuint _uiProgram)
{
	glUseProgram(_uiProgram);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	//GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the shape's textures (if any).
	BindTextures(_uiProgram);

	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetProjectionMatrix()));
	glUniform3fv(glGetUniformLocation(_uiProgram, "v3fCameraPosition"), 1, glm::value_ptr(*CCamera::GetMainCamera()->GetTransform()->GetPosition()));

	glUniform1f(glGetUniformLocation(_uiProgram, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(_uiProgram, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));

	glDrawElements(GL_TRIANGLES, m_poMesh->GetTriIndices()->size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}