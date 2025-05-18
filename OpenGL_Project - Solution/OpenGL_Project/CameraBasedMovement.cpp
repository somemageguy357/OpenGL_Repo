#include "CameraBasedMovement.h"
#include "Shape.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Camera.h"
#include "Math.h"

#include <iostream>

void CCameraBasedMovement::Update(CShape* _poShape)
{
	m_v3fMoveDir = { 0.0f, 0.0f, 0.0f };

	if (CInputManager::GetKey(GLFW_KEY_W) == true)
	{
		m_v3fMoveDir += *CCamera::GetMainCamera()->GetForwardDirection();
	}

	else if (CInputManager::GetKey(GLFW_KEY_S) == true)
	{
		m_v3fMoveDir -= *CCamera::GetMainCamera()->GetForwardDirection();
	}

	//if (CInputManager::GetKey(GLFW_KEY_A) == true)
	//{
	//	m_v3fMoveDir += *CCamera::GetMainCamera()->GetForwardDirection();
	//}

	//else if (CInputManager::GetKey(GLFW_KEY_D) == true)
	//{
	//	m_v3fMoveDir -= *CCamera::GetMainCamera()->GetForwardDirection();
	//}

	if (CInputManager::GetKey(GLFW_KEY_Q) == true)
	{
		m_v3fMoveDir += glm::vec3{ 0.0f, 1.0f, 0.0f };
	}

	else if (CInputManager::GetKey(GLFW_KEY_E) == true)
	{
		m_v3fMoveDir -= glm::vec3{ 0.0f, 1.0f, 0.0f };
	}

	glm::vec3 v3fMoveDiff = CMath::Normalize(m_v3fMoveDir) * m_fMoveSpeed * CTimeManager::GetDeltaTime();
	_poShape->GetTransform()->AddPosition(v3fMoveDiff);

	std::cout << "Position: (" << _poShape->GetTransform()->GetPosition()->x << ", " << _poShape->GetTransform()->GetPosition()->y << ", " << _poShape->GetTransform()->GetPosition()->z << ")\n";
}