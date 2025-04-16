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

bool CProgramSettings::m_bWireframeOn = false;
bool CProgramSettings::m_bFaceCullingOn = false;
bool CProgramSettings::m_bDepthTestingOn = false;
bool CProgramSettings::m_bTextureBlendingOn = false;

void CProgramSettings::Update()
{
	if (CInputManager::GetKeyDown(GLFW_KEY_F) == true)
	{
		ToggleWireframe();
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