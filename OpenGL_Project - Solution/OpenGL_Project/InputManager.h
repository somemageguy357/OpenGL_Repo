/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : InputManager.h
Description : Static class that handles input checks for keys, mouse buttons, and mouse position and 
				allows cursor visibility to change.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "WindowManager.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <vector>

//Static class that handles input checks for keys, mouse buttons, and mouse position and allows cursor visibility to change.
class CInputManager
{
public:
	//The visibility mode of the cursor.
	enum class ECursorMode
	{
		Visible,
		Hidden,
		Disabled,
	};

	/// <summary>
	/// Checks if the key referenced in the given key code is being pressed.
	/// </summary>
	/// <param name="_iKeyCode:">The code for the key to check.</param>
	/// <returns>True if the key is being pressed, false if not.</returns>
	static bool GetKey(int _iKeyCode);

	/// <summary>
	/// Checks if the key referenced in the given key code was pressed down on this frame.
	/// </summary>
	/// <param name="_iKeyCode:">The code for the key to check.</param>
	/// <returns>True if the key has been pressed down this frame, false if not.</returns>
	static bool GetKeyDown(int _iKeyCode);

	/// <summary>
	/// Checks if the key referenced in the given key code was released on this frame.
	/// </summary>
	/// <param name="_iKeyCode:">The code for the key to check.</param>
	/// <returns>True if the key has been released on this frame, false if not.</returns>
	static bool GetKeyUp(int _iKeyCode);

	/// <summary>
	/// Checks if the mouse button referenced in the given button code is being clicked/held down.
	/// </summary>
	/// <param name="_iButtonCode:">The code for the mouse button to check.</param>
	/// <returns>True if the mouse button is being clicked/held down, false if not.</returns>
	static bool GetButton(int _iButtonCode);

	/// <summary>
	/// Checks if the mouse button referenced in the given button code was clicked on this frame.
	/// </summary>
	/// <param name="_iButtonCode:">The code for the mouse button to check.</param>
	/// <returns>True if the mouse button was clicked on this frame, false if not.</returns>
	static bool GetButtonDown(int _iButtonCode);

	/// <summary>
	/// Checks if the mouse button referenced in the given button code was released on this frame.
	/// </summary>
	/// <param name="_iButtonCode:">The code for the mouse button to check.</param>
	/// <returns>True if the mouse button was released on this frame, false if not.</returns>
	static bool GetButtonUp(int _iButtonCode);

	/// <summary>
	/// Gets the mouse position in pixel coordinates of the current window, with the top-left corner being (0,0).
	/// </summary>
	/// <returns>The mouse position.</returns>
	static glm::vec2 GetMousePosition();

	/// <summary>
	/// Sets the visibility mode of the cursor. Visible always displays the cursor. Hidden hides the cursor while
	/// it is over the window, but allows it to exit the window. Disabled hides the cursor and locks it to the center, preventing
	/// it from exiting the window.
	/// </summary>
	/// <param name="_eCursorMode:">The cursor mode to use.</param>
	static void SetMouseCursorMode(ECursorMode _eCursorMode);

	/// <summary>
	/// Gets the mode of the cursor.
	/// </summary>
	/// <returns>The mode of the cursor.</returns>
	static ECursorMode GetCursorMode();

	/// <summary>
	/// Clears the vectors containing all keys and mouse buttons that were pressed and/or released this frame.
	/// This is to be called at the end of the main update loop.
	/// </summary>
	static void ClearInputs();

	/// <summary>
	/// Enables the callback functions for key and mouse button inputs, as well as the mouse position.
	/// </summary>
	static void EnableCallbackFunctions();

	/// <summary>
	/// Enables or disables the callback function for reading text input.
	/// </summary>
	/// <param name="_bEnable:">Enables text input if true.</param>
	static void SetEnableTextInput(bool _bEnable);

private:
	//Vectors containing all keys and mouse buttons that were pressed/released each frame.
	static std::vector<int> m_oVecKeysPressedThisFrame;
	static std::vector<int> m_oVecKeysReleasedThisFrame;

	static std::vector<int> m_oVecButtonsClickedThisFrame;
	static std::vector<int> m_oVecButtonsReleasedThisFrame;

	//Stores mouse position.
	static glm::vec2 m_v2fMousePosition;

	//The current mode of the cursor.
	static ECursorMode m_eCursorMode;

	CInputManager() {};
	~CInputManager() {};

	//Callback function for key inputs.
	static void KeyInput(GLFWwindow* _poWindow, int _iKeyCode, int _iScanCode, int _iAction, int _iMods);

	//Callback function for text inputs.
	static void TextInput(GLFWwindow* _poWindow, unsigned int _uiCodePoint);

	//Callback function for mouse button inputs.
	static void MouseInput(GLFWwindow* _poWindow, int _iButtonCode, int _iAction, int _iMods);

	//Callback function for reading the mouse position.
	static void MousePosition(GLFWwindow* _poWindow, double _dX, double _dY);
};