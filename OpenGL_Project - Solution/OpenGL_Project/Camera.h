/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Camera.h
Description : Used to render objects in a 3D space.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Shape.h"
#include "Texture.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Used to render objects to in a 3D space. 
class CCamera : public CTransform
{
public:
	CCamera() = delete;

	/// <summary>
	/// Creates a camera whose view frustrum is set using the given window width and height values. The position (0.0f, 0.0f, 0.0f)
	/// and rotation (0.0f, 0.0f, 0.0f) of the camera are set to their default values.
	/// </summary>
	/// <param name="_kiWindowWidth:">The pixel width of the window.</param>
	/// <param name="_kiWindowHeight:">The pixel height of the window.</param>
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight);

	/// <summary>
	/// Creates a camera whose view frustrum is set using the given window width and height values as well as its position. 
	/// The rotation (0.0f, 0.0f, 0.0f) of the camera is set to its default value.
	/// </summary>
	/// <param name="_kiWindowWidth:">The pixel width of the window.</param>
	/// <param name="_kiWindowHeight:">The pixel height of the window.</param>
	/// <param name="_v3fPosition:">The starting position of the camera.</param>
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a camera whose view frustrum is set using the given window width and height values as well as its position and rotation. 
	/// </summary>
	/// <param name="_kiWindowWidth:">The pixel width of the window.</param>
	/// <param name="_kiWindowHeight:">The pixel height of the window.</param>
	/// <param name="_v3fPosition:">The starting position of the camera.</param>
	/// <param name="_v3fRotation:">The starting rotation of the camera.</param>
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	~CCamera();

	/// <summary>
	/// Updates the camera's View Matrix to reflect any transform changes it has received.
	/// </summary>
	void Update();

	/// <summary>
	/// Renders the given shape to the window using the given shader program.
	/// </summary>
	/// <param name="_uiProgram:">The shader program to use.</param>
	/// <param name="_poShape:">The shape to render.</param>
	/// <param name="_fCurrentTime:">The current lifetime of the program.</param>
	void Render(GLuint _uiProgram, CShape* _poShape, float _fCurrentTime);

	/// <summary>
	/// Sets the target position of the camera.
	/// </summary>
	/// <param name="_v3fTargetPosition:">The target position.</param>
	void SetTargetPosition(glm::vec3 _v3fTargetPosition);

	//glm::mat4* GetViewMatrix();

	//glm::mat4* GetProjectionMatrix();


private:
	//The camera's forward/view direction.
	glm::vec3 m_v3fCamForwardDir = glm::vec3(0.0f, 0.0f, -1.0f);

	//The camera's target position.
	glm::vec3 m_v3fTargetPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//The camera's upwards position.
	glm::vec3 m_v3fCamUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	//The camera's view matrix.
	glm::mat4 m_matView;

	//The camera's projection matrix.
	glm::mat4 m_matProjection;

	//Sets up the camera's view and projection matrices. Called from the constructors.
	void CameraSetup(const int _kiWindowWidth, const int _kiWindowHeight);
};