/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Camera.cpp
Description : Contains function definitions for Camera.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Camera.h"
#include "TimeManager.h"
#include "WindowManager.h"

CCamera::CCamera(const bool _kbIsPerspective)
{
	m_bIsPerspective = _kbIsPerspective;
	CameraSetup();
}

CCamera::CCamera(const bool _kbIsPerspective, glm::vec3 _v3fPosition)
{
	m_bIsPerspective = _kbIsPerspective;
	m_oTransform = CTransform(_v3fPosition);
	CameraSetup();
}

CCamera::CCamera(const bool _kbIsPerspective, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
{
	m_bIsPerspective = _kbIsPerspective;
	m_oTransform = CTransform(_v3fPosition, _v3fRotation);
	CameraSetup();
}

CCamera::~CCamera() {}

void CCamera::Update()
{
	m_matView = glm::lookAt(*m_oTransform.GetPosition(), *m_oTransform.GetPosition() + m_v3fCamForwardDir, m_v3fCamUpDir); //Look at position.
}

void CCamera::Render(GLuint _uiProgram, CShape* _poShape)
{
	glUseProgram(_uiProgram);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*_poShape->GetVAO());

	//Bind the shape's textures (if any).
	_poShape->BindTextures(_uiProgram);

	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*_poShape->GetTransform()->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(m_matView));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(m_matProjection));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void CCamera::SetTargetPosition(glm::vec3 _v3fTargetPosition)
{
	m_v3fTargetPosition = _v3fTargetPosition;
}

CTransform* CCamera::GetTransform()
{
	return &m_oTransform;
}

void CCamera::SetProjectionSpace(bool _bIsPerspective, std::vector<CShape*>* _poVecShapePtrs)
{
	if (m_bIsPerspective != _bIsPerspective)
	{
		m_bIsPerspective = _bIsPerspective;

		if (m_bIsPerspective == true)
		{
			for (size_t i = 0; i < _poVecShapePtrs->size(); i++)
			{
				(*_poVecShapePtrs)[i]->GetTransform()->SetScaleMultiplier(1.0f);
			}

			CameraSetup();
		}

		else
		{
			for (size_t i = 0; i < _poVecShapePtrs->size(); i++)
			{
				(*_poVecShapePtrs)[i]->GetTransform()->SetScaleMultiplier(400.0f);
			}

			CameraSetup();
		}
	}
}

bool CCamera::GetProjectionSpace()
{
	return m_bIsPerspective;
}

//glm::mat4* CCamera::GetViewMatrix()
//{
//	return &matView;
//}
//
//glm::mat4* CCamera::GetProjectionMatrix()
//{
//	return &matProjection;
//}

void CCamera::CameraSetup()
{
	m_matView = glm::lookAt(*m_oTransform.GetPosition(), *m_oTransform.GetPosition() + m_v3fCamForwardDir, m_v3fCamUpDir); //Look at position.
	//matView = glm::lookAt(v3fCamPosition, v3fCamTargetPosition, v3fCamUpDir); //Look at target.

	if (m_bIsPerspective == true)
	{
		m_matProjection = glm::perspective(glm::radians(45.0f), (float)CWindowManager::GetWidth() / (float)CWindowManager::GetHeight(), 0.1f, 100.0f);
	}

	else
	{
		m_matProjection = glm::ortho(-(float)CWindowManager::GetWidth() * 0.5f, (float)CWindowManager::GetWidth() * 0.5f, -(float)CWindowManager::GetHeight() * 0.5f, (float)CWindowManager::GetHeight() * 0.5f, 0.1f, 100.0f);
	}
}