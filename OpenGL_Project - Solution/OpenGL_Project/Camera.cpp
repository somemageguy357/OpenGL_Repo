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
	if (CInputManager::GetKey(GLFW_KEY_1) == true)
	{
		SetCameraMode(ECameraMode::Free);
	}

	else if (CInputManager::GetKey(GLFW_KEY_2) == true)
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

	//Reset camera position.
	if (CInputManager::GetKey(GLFW_KEY_R) == true)
	{
		m_oTransform.SetPosition({ 0.0f, 0.0f, 3.0f });
	}
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

	glDrawElements(GL_TRIANGLES, _poShape->GetTriIndices().size(), GL_UNSIGNED_INT, 0);

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

		//Perspective
		if (m_bIsPerspective == true)
		{
			for (size_t i = 0; i < _poVecShapePtrs->size(); i++)
			{
				(*_poVecShapePtrs)[i]->GetTransform()->SetScaleMultiplier(1.0f);
			}

			CameraSetup();
		}

		//Orthographic
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

void CCamera::SetCameraMode(ECameraMode _eCameraMode)
{
	m_eCameraMode = _eCameraMode;

	CInputManager::SetMouseCursorMode(CInputManager::ECursorMode::Disabled);
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
	glm::vec3 v3fRightDir = CMath::Normalize(glm::cross(m_v3fCamForwardDir, m_v3fCamUpDir));

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
		v3fMoveDir -= v3fRightDir;
	}

	if (CInputManager::GetKey(GLFW_KEY_D) == true)
	{
		v3fMoveDir += v3fRightDir;
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
	m_fOrbitAngle += TriBool() * CTimeManager::GetDeltaTime() * m_fOrbitMoveSpeed;

	glm::vec3 v3fNewPosition = { sin(m_fOrbitAngle) * m_fOrbitRadius, m_fOrbitHeight, cos(m_fOrbitAngle) * m_fOrbitRadius };
	m_oTransform.SetPosition(v3fNewPosition);

	m_matView = glm::lookAt(*m_oTransform.GetPosition(), { 0.0f, 0.0f, 0.0f }, m_v3fCamUpDir); //Look at target.
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
	SetCameraMode(CCamera::ECameraMode::Free);

	if (m_bIsPerspective == true)
	{
		m_matProjection = glm::perspective(glm::radians(45.0f), (float)CWindowManager::GetWidth() / (float)CWindowManager::GetHeight(), 0.1f, 100.0f);
	}

	else
	{
		m_matProjection = glm::ortho(-(float)CWindowManager::GetWidth() * 0.5f, (float)CWindowManager::GetWidth() * 0.5f, -(float)CWindowManager::GetHeight() * 0.5f, (float)CWindowManager::GetHeight() * 0.5f, 0.1f, 100.0f);
	}
}