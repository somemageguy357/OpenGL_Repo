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
glm::vec2 CInputManager::m_v2fMousePosition = { 0.0f, 0.0f };
CInputManager::ECursorMode CInputManager::m_eCursorMode;

bool CInputManager::GetKey(int _iKeyCode)
{
	if (glfwGetKey(CWindowManager::GetWindow(), _iKeyCode) == true)
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
	if (glfwGetMouseButton(CWindowManager::GetWindow(), _iButtonCode) == true)
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

		if (glfwRawMouseMotionSupported() == true)
		{
			glfwSetInputMode(CWindowManager::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		m_v2fMousePosition.x = CWindowManager::GetWidth() / 2;
		m_v2fMousePosition.y = CWindowManager::GetHeight() / 2;
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
}

void CInputManager::EnableCallbackFunctions()
{
	glfwSetKeyCallback(CWindowManager::GetWindow(), KeyInput);
	glfwSetMouseButtonCallback(CWindowManager::GetWindow(), MouseInput);
	glfwSetCursorPosCallback(CWindowManager::GetWindow(), MousePosition);
	//glfwSetCharCallback(CWindowManager::GetWindow(), TextInput); //should enable via keybind in program settings.
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

void CInputManager::MousePosition(GLFWwindow* _poWindow, double _dX, double _dY)
{
	m_v2fMousePosition = glm::vec2(_dX, _dY);
}