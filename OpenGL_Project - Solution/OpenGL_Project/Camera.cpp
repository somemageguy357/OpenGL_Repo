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
#include "InputManager.h"
#include "Math.h"

#include <iostream>

CCamera* CCamera::m_poMainCamera = nullptr;

CCamera::CCamera(const bool _kbIsPerspective, ECameraMode _eCameraMode, glm::vec3 _v3fPosition, glm::vec3 _v3fForwardDir)
{
	m_bIsPerspective = _kbIsPerspective;
	m_oTransform = CTransform(_v3fPosition);
	m_v3fCamForwardDir = CMath::Normalize(_v3fForwardDir);
	m_fYaw = glm::degrees(atan2(m_v3fCamForwardDir.z, m_v3fCamForwardDir.x));

	SetCameraMode(_eCameraMode);
	CameraSetup();
}

CCamera::~CCamera() {}

void CCamera::Update()
{
	if (CInputManager::GetMouseScroll(1) == true)
	{
		UpdateFOV(1);
	}

	else if (CInputManager::GetMouseScroll(-1) == true)
	{
		UpdateFOV(-1);
	}

	if (CInputManager::GetKey(GLFW_KEY_9) == true)
	{
		SetCameraMode(ECameraMode::Free);
	}

	else if (CInputManager::GetKey(GLFW_KEY_0) == true)
	{
		SetCameraMode(ECameraMode::Orbital);
	}

	if (m_eCameraMode == ECameraMode::Free)
	{
		FreeCamControls();
	}

	else if (m_eCameraMode == ECameraMode::Orbital)
	{
		OrbitalCamControls();
	}
}

void CCamera::SetTargetPosition(glm::vec3 _v3fTargetPosition)
{
	m_v3fTargetPosition = _v3fTargetPosition;
}

CTransform* CCamera::GetTransform()
{
	return &m_oTransform;
}

bool CCamera::GetProjectionSpace()
{
	return m_bIsPerspective;
}

void CCamera::SetCameraMode(ECameraMode _eCameraMode)
{
	m_eCameraMode = _eCameraMode;

	CInputManager::SetMouseCursorMode(CInputManager::ECursorMode::Disabled);

	m_fPrevMouseX = (float)CWindowManager::GetWidth() / 2;
	m_fPrevMouseY = (float)CWindowManager::GetHeight() / 2;
}

void CCamera::ToggleOrbitMovement()
{
	m_bEnableOrbitMovement = !m_bEnableOrbitMovement;
}

CCamera* CCamera::GetMainCamera()
{
	return m_poMainCamera;
}

glm::mat4* CCamera::GetViewMatrix()
{
	return &m_matView;
}

glm::mat4* CCamera::GetProjectionMatrix()
{
	return &m_matProjection;
}

glm::vec3* CCamera::GetForwardDirection()
{
	return &m_v3fCamForwardDir;
}

glm::vec3* CCamera::GetRightDirection()
{
	return &m_v3fCamRightDir;
}

void CCamera::UpdateFOV(double _dScrollDirection)
{
	if (_dScrollDirection == -1 && m_fFOV < m_fMaxFOV)
	{
		m_fFOV += 5.0f;
	}

	else if (_dScrollDirection == 1 && m_fFOV > m_fMinFOV)
	{
		m_fFOV -= 5.0f;
	}

	m_matProjection = glm::perspective(glm::radians(m_fFOV), (float)CWindowManager::GetWidth() / (float)CWindowManager::GetHeight(), 0.1f, 100.0f);
}

void CCamera::FreeCamControls()
{
	glm::vec2 v2fMousePos = CInputManager::GetMousePosition();

	m_fOffsetX = v2fMousePos.x - m_fPrevMouseX;
	m_fOffsetY = m_fPrevMouseY - v2fMousePos.y;
	m_fPrevMouseX = v2fMousePos.x;
	m_fPrevMouseY = v2fMousePos.y;

	float fMouseSensitivity = 10.0f * CTimeManager::GetDeltaTime();
	m_fOffsetX *= fMouseSensitivity;
	m_fOffsetY *= fMouseSensitivity;

	m_fYaw += m_fOffsetX;
	m_fPitch += m_fOffsetY;

	m_fPitch = glm::clamp(m_fPitch, -89.0f, 89.0f);

	glm::vec3 v3fLookDir =
	{
		cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch)),
		sin(glm::radians(m_fPitch)),
		sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch))
	};

	m_v3fCamForwardDir = CMath::Normalize(v3fLookDir);
	m_v3fCamRightDir = CMath::Normalize(glm::cross(m_v3fCamForwardDir, m_v3fCamUpDir));

	//std::cout << "Mouse: " << v2fMousePos.x << "," << v2fMousePos.y << " | Prev: " << m_fPrevMouseX << "," << m_fPrevMouseY << " | Offset: " << m_fOffsetX << "," << m_fOffsetY << std::endl;

	//Create vector for sum movement direction.
	glm::vec3 v3fMoveDir = { 0.0f, 0.0f, 0.0f };

	if (CInputManager::GetKey(GLFW_KEY_W) == true)
	{
		v3fMoveDir += m_v3fCamForwardDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_S) == true)
	{
		v3fMoveDir -= m_v3fCamForwardDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_A) == true)
	{
		v3fMoveDir -= m_v3fCamRightDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_D) == true)
	{
		v3fMoveDir += m_v3fCamRightDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_E) == true)
	{
		v3fMoveDir += m_v3fCamUpDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_Q) == true)
	{
		v3fMoveDir -= m_v3fCamUpDir;
	}

	//Move camera using sum of direction * delta time.
	m_oTransform.AddPosition(CMath::Normalize(v3fMoveDir) * CTimeManager::GetDeltaTime() * 5.0f);

	m_matView = glm::lookAt(*m_oTransform.GetPosition(), *m_oTransform.GetPosition() + m_v3fCamForwardDir, m_v3fCamUpDir); //Look at position.
}

void CCamera::OrbitalCamControls()
{
	//if (CInputManager::GetKeyDown(GLFW_KEY_TAB) == true)
	//{
	//	ToggleOrbitMovement();
	//}

	if (m_bEnableOrbitMovement == true)
	{
		m_fOrbitAngle += TriBool() * CTimeManager::GetDeltaTime() * m_fOrbitMoveSpeed; //--Manual rotation.
		//m_fOrbitAngle += CTimeManager::GetDeltaTime() * m_fOrbitMoveSpeed; //--Auto rotation.

		glm::vec3 v3fNewPosition = { sin(m_fOrbitAngle) * m_fOrbitRadius, m_fOrbitHeight, cos(m_fOrbitAngle) * m_fOrbitRadius };
		m_oTransform.SetPosition(v3fNewPosition);

		m_matView = glm::lookAt(*m_oTransform.GetPosition(), m_v3fTargetPosition, m_v3fCamUpDir); //Look at target.

		m_v3fCamForwardDir = CMath::Normalize(m_v3fTargetPosition - *m_oTransform.GetPosition());
		m_v3fCamRightDir = CMath::Normalize(glm::cross(m_v3fCamForwardDir, m_v3fCamUpDir));

		//std::cout << "Position: (" << m_oTransform.GetPosition()->x << ", " << m_oTransform.GetPosition()->y << ", " << m_oTransform.GetPosition()->z << ") | ";
		//std::cout << "Forward Dir: (" << m_v3fCamForwardDir.x << ", " << m_v3fCamForwardDir.y << ", " << m_v3fCamForwardDir.z << ")\t|\t";
		//std::cout << "Right Dir: (" << m_v3fCamRightDir.x << ", " << m_v3fCamRightDir.y << ", " << m_v3fCamRightDir.z << ")\n";
	}
}

int CCamera::TriBool()
{
	int iValue = 0;

	if (CInputManager::GetKey(GLFW_KEY_A) == true)
	{
		iValue -= 1;
	}

	if (CInputManager::GetKey(GLFW_KEY_D) == true)
	{
		iValue += 1;
	}

	return iValue;
}

void CCamera::CameraSetup()
{
	if (m_poMainCamera == nullptr)
	{
		m_poMainCamera = this;
	}

	if (m_bIsPerspective == true)
	{
		m_matProjection = glm::perspective(glm::radians(m_fFOV), (float)CWindowManager::GetWidth() / (float)CWindowManager::GetHeight(), 0.1f, 100.0f);
	}

	else
	{
		m_matProjection = glm::ortho(-(float)CWindowManager::GetWidth() * 0.5f, (float)CWindowManager::GetWidth() * 0.5f, -(float)CWindowManager::GetHeight() * 0.5f, (float)CWindowManager::GetHeight() * 0.5f, 0.1f, 100.0f);
	}
}