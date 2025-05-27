/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : CameraBasedMovement.cpp
Description : Contains function definitions for CameraBasedMovement.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "CameraBasedMovement.h"
#include "Object.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Camera.h"
#include "Math.h"

#include <iostream>

CCameraBasedMovement::CCameraBasedMovement(glm::vec3 _v3fStartingPosition)
{
	m_v3fStartingPosition = _v3fStartingPosition;
}

void CCameraBasedMovement::Update(CTransform* _poTransform)
{
	if (CInputManager::GetKeyDown(GLFW_KEY_R) == true)
	{
		_poTransform->SetPosition(m_v3fStartingPosition);
		return;
	}

	m_v3fMoveDir = { 0.0f, 0.0f, 0.0f };

	if (CInputManager::GetKey(GLFW_KEY_W) == true)
	{
		glm::vec3 v3fCamForward = *CCamera::GetMainCamera()->GetForwardDirection();
		m_v3fMoveDir += glm::vec3{ v3fCamForward.x, 0.0f, v3fCamForward.z};
	}

	else if (CInputManager::GetKey(GLFW_KEY_S) == true)
	{
		glm::vec3 v3fCamForward = *CCamera::GetMainCamera()->GetForwardDirection();
		m_v3fMoveDir -= glm::vec3{ v3fCamForward.x, 0.0f, v3fCamForward.z };
	}

	if (CInputManager::GetKey(GLFW_KEY_A) == true)
	{
		glm::vec3 v3fCamRight = *CCamera::GetMainCamera()->GetRightDirection();
		m_v3fMoveDir -= glm::vec3{ v3fCamRight.x, 0.0f, v3fCamRight.z };
	}

	else if (CInputManager::GetKey(GLFW_KEY_D) == true)
	{
		glm::vec3 v3fCamRight = *CCamera::GetMainCamera()->GetRightDirection();
		m_v3fMoveDir += glm::vec3{ v3fCamRight.x, 0.0f, v3fCamRight.z };
	}

	if (CInputManager::GetKey(GLFW_KEY_Q) == true)
	{
		m_v3fMoveDir += glm::vec3{ 0.0f, 1.0f, 0.0f };
	}

	else if (CInputManager::GetKey(GLFW_KEY_E) == true)
	{
		m_v3fMoveDir -= glm::vec3{ 0.0f, 1.0f, 0.0f };
	}

	glm::vec3 v3fMoveDiff = CMath::Normalize(m_v3fMoveDir) * m_fMoveSpeed * CTimeManager::GetDeltaTime();
	_poTransform->AddPosition(v3fMoveDiff);

	//std::cout << "Position: (" << _poShape->GetTransform()->GetPosition()->x << ", " << _poShape->GetTransform()->GetPosition()->y << ", " << _poShape->GetTransform()->GetPosition()->z << ")\n";
}