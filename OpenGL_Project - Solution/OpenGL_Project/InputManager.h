#pragma once
#include "WindowManager.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <vector>

class CInputManager
{
public:
	enum class ECursorMode
	{
		Visible,
		Hidden,
		Disabled,
	};

	static bool GetKey(int _iKeyCode);

	static bool GetKeyDown(int _iKeyCode);

	static bool GetKeyUp(int _iKeyCode);

	static bool GetButton(int _iButtonCode);

	static bool GetButtonDown(int _iButtonCode);

	static bool GetButtonUp(int _iButtonCode);

	static glm::vec2 GetMousePosition();

	static void SetMouseCursorMode(ECursorMode _eCursorMode);

	static void ClearInputs();

	static void EnableCallbackFunctions();

	static void SetEnableTextInput(bool _bEnable);

private:
	static std::vector<int> m_oVecKeysPressedThisFrame;
	static std::vector<int> m_oVecKeysReleasedThisFrame;

	static std::vector<int> m_oVecButtonsClickedThisFrame;
	static std::vector<int> m_oVecButtonsReleasedThisFrame;

	static glm::vec2 m_v2fMousePosition;

	CInputManager() {};
	~CInputManager() {};

	static void KeyInput(GLFWwindow* _poWindow, int _iKeyCode, int _iScanCode, int _iAction, int _iMods);

	static void TextInput(GLFWwindow* _poWindow, unsigned int _uiCodePoint);

	static void MouseInput(GLFWwindow* _poWindow, int _iButtonCode, int _iAction, int _iMods);

	static void MousePosition(GLFWwindow* _poWindow, double _dX, double _dY);
};