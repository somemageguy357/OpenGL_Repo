/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ProgramSettings.cpp
Description : Contains function definitions for ProgramSettings.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "ProgramSettings.h"
#include "InputManager.h"

#include <iostream>

bool CProgramSettings::m_bWireframeOn = false;
bool CProgramSettings::m_bFaceCullingOn = false;
bool CProgramSettings::m_bDepthTestingOn = false;
bool CProgramSettings::m_bTextureBlendingOn = false;

void CProgramSettings::Update()
{
	if (CInputManager::GetKeyDown(GLFW_KEY_1) == true)
	{
		if (CInputManager::GetCursorMode() == CInputManager::ECursorMode::Disabled || CInputManager::GetCursorMode() == CInputManager::ECursorMode::Hidden)
		{
			CInputManager::SetMouseCursorMode(CInputManager::ECursorMode::Visible);
		}

		else if (CInputManager::GetCursorMode() == CInputManager::ECursorMode::Visible)
		{
			CInputManager::SetMouseCursorMode(CInputManager::ECursorMode::Disabled);
		}
	}

	else if (CInputManager::GetKeyDown(GLFW_KEY_2) == true)
	{
		ToggleWireframe();
	}

	else if (CInputManager::GetKeyDown(GLFW_KEY_3) == true)
	{
		glm::vec2 v2fMousePosition = CInputManager::GetMousePosition();
		std::cout << "Mouse Position: (" << v2fMousePosition.x << ", " << v2fMousePosition.y << ")\n";
	}

	else if (CInputManager::GetKeyDown(GLFW_KEY_C) == true)
	{
		ToggleFaceCulling();
	}
}

void CProgramSettings::SetWireframe(bool _bOn)
{
	m_bWireframeOn = _bOn;

	if (m_bWireframeOn == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void CProgramSettings::SetFaceCulling(bool _bOn)
{
	m_bFaceCullingOn = _bOn;

	if (m_bFaceCullingOn == true)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	else
	{
		glDisable(GL_CULL_FACE);
	}
}

void CProgramSettings::SetDepthTesting(bool _bOn)
{
	m_bDepthTestingOn = _bOn;

	if (m_bDepthTestingOn == true)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void CProgramSettings::SetTextureBlending(bool _bOn)
{
	m_bTextureBlendingOn = _bOn;

	if (m_bTextureBlendingOn == true)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	else
	{
		glDisable(GL_BLEND);
	}
}

void CProgramSettings::ToggleWireframe()
{
	m_bWireframeOn = !m_bWireframeOn;

	if (m_bWireframeOn == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void CProgramSettings::ToggleFaceCulling()
{
	m_bFaceCullingOn = !m_bFaceCullingOn;

	if (m_bFaceCullingOn == true)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	else
	{
		glDisable(GL_CULL_FACE);
	}
}