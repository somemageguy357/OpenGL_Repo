/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : InputManager.cpp
Description : Contains function definitions for InputManager.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "InputManager.h"
#include <iostream>

std::vector<int> CInputManager::m_oVecKeysPressedThisFrame;
std::vector<int> CInputManager::m_oVecKeysReleasedThisFrame;
std::vector<int> CInputManager::m_oVecButtonsClickedThisFrame;
std::vector<int> CInputManager::m_oVecButtonsReleasedThisFrame;
double CInputManager::m_dScrollDirection = 0.0;
glm::vec2 CInputManager::m_v2fMousePosition = { 0.0f, 0.0f };
CInputManager::ECursorMode CInputManager::m_eCursorMode;

bool CInputManager::GetKey(int _iKeyCode)
{
	if (glfwGetKey(CWindowManager::GetWindow(), _iKeyCode) == 1)
	{
		return true;
	}

	return false;
}

bool CInputManager::GetKeyDown(int _iKeyCode)
{
	for (size_t i = 0; i < m_oVecKeysPressedThisFrame.size(); i++)
	{
		if (_iKeyCode == m_oVecKeysPressedThisFrame[i])
		{
			return true;
		}
	}

	return false;
}

bool CInputManager::GetKeyUp(int _iKeyCode)
{
	for (size_t i = 0; i < m_oVecKeysReleasedThisFrame.size(); i++)
	{
		if (_iKeyCode == m_oVecKeysReleasedThisFrame[i])
		{
			return true;
		}
	}

	return false;
}

bool CInputManager::GetButton(int _iButtonCode)
{
	if (glfwGetMouseButton(CWindowManager::GetWindow(), _iButtonCode) == 1)
	{
		return true;
	}

	return false;
}

bool CInputManager::GetButtonDown(int _iButtonCode)
{
	for (size_t i = 0; i < m_oVecButtonsClickedThisFrame.size(); i++)
	{
		if (_iButtonCode == m_oVecButtonsClickedThisFrame[i])
		{
			return true;
		}
	}

	return false;
}

bool CInputManager::GetButtonUp(int _iButtonCode)
{
	for (size_t i = 0; i < m_oVecButtonsReleasedThisFrame.size(); i++)
	{
		if (_iButtonCode == m_oVecButtonsReleasedThisFrame[i])
		{
			return true;
		}
	}

	return false;
}

bool CInputManager::GetMouseScroll(double _dScrollValue)
{
	if (m_dScrollDirection == _dScrollValue)
	{
		return true;
	}

	return false;
}

glm::vec2 CInputManager::GetMousePosition()
{
	return m_v2fMousePosition;
}

void CInputManager::SetMouseCursorMode(ECursorMode _eCursorMode)
{
	m_eCursorMode = _eCursorMode;

	if (_eCursorMode == ECursorMode::Visible)
	{
		glfwSetInputMode(CWindowManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	else if (_eCursorMode == ECursorMode::Hidden)
	{
		glfwSetInputMode(CWindowManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	else if (_eCursorMode == ECursorMode::Disabled)
	{
		glfwSetInputMode(CWindowManager::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (glfwRawMouseMotionSupported() == 1)
		{
			glfwSetInputMode(CWindowManager::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		m_v2fMousePosition.x = (float)CWindowManager::GetWidth() / 2;
		m_v2fMousePosition.y = (float)CWindowManager::GetHeight() / 2;
	}
}

CInputManager::ECursorMode CInputManager::GetCursorMode()
{
	return m_eCursorMode;
}

void CInputManager::ClearInputs()
{
	m_oVecKeysPressedThisFrame.clear();
	m_oVecKeysReleasedThisFrame.clear();
	m_oVecButtonsClickedThisFrame.clear();
	m_oVecButtonsReleasedThisFrame.clear();
	m_dScrollDirection = 0.0;
}

void CInputManager::EnableCallbackFunctions()
{
	glfwSetKeyCallback(CWindowManager::GetWindow(), KeyInput);
	glfwSetMouseButtonCallback(CWindowManager::GetWindow(), MouseInput);
	glfwSetScrollCallback(CWindowManager::GetWindow(), MouseScroll);
	glfwSetCursorPosCallback(CWindowManager::GetWindow(), MousePosition);
}

void CInputManager::SetEnableTextInput(bool _bEnable)
{
	if (_bEnable == true)
	{
		glfwSetCharCallback(CWindowManager::GetWindow(), TextInput);
	}

	else
	{
		glfwSetCharCallback(CWindowManager::GetWindow(), 0);
	}
}

void CInputManager::KeyInput(GLFWwindow* _poWindow, int _iKeyCode, int _iScanCode, int _iAction, int _iMods)
{
	if (_iAction == GLFW_PRESS)
	{
		m_oVecKeysPressedThisFrame.push_back(_iKeyCode);
	}

	else if (_iAction == GLFW_RELEASE)
	{
		m_oVecKeysReleasedThisFrame.push_back(_iKeyCode);
	}
}

void CInputManager::TextInput(GLFWwindow* _poWindow, unsigned int _uiCodePoint)
{
	std::cout << "Input: " << (unsigned char)_uiCodePoint << std::endl;
}

void CInputManager::MouseInput(GLFWwindow* _poWindow, int _iButtonCode, int _iAction, int _iMods)
{
	if (_iAction == GLFW_PRESS)
	{
		m_oVecButtonsClickedThisFrame.push_back(_iButtonCode);
	}

	else if (_iAction == GLFW_RELEASE)
	{
		m_oVecButtonsReleasedThisFrame.push_back(_iButtonCode);
	}
}

void CInputManager::MouseScroll(GLFWwindow* _poWindow, double _dX, double _dY)
{
	m_dScrollDirection = _dY;
}

void CInputManager::MousePosition(GLFWwindow* _poWindow, double _dX, double _dY)
{
	m_v2fMousePosition = glm::vec2(_dX, _dY);
}