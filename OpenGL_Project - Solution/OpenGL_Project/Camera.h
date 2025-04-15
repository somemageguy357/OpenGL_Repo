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
class CCamera
{
public:
	CCamera() = delete;

	/// <summary>
	/// Creates a camera whose view frustrum is set using the window's width and height values. The position (0.0f, 0.0f, 0.0f)
	/// and rotation (0.0f, 0.0f, 0.0f) of the camera are set to their default values.
	/// </summary>
	/// <param name="_kbIsPerspective:">Is the camera perspective or orthographic?</param>
	CCamera(const bool _kbIsPerspective);

	/// <summary>
	/// Creates a camera whose view frustrum is set using the window's width and height values as well as the given position. 
	/// The rotation (0.0f, 0.0f, 0.0f) of the camera is set to its default value.
	/// </summary>
	/// <param name="_kbIsPerspective:">Is the camera perspective or orthographic?</param>
	/// <param name="_v3fPosition:">The starting position of the camera.</param>
	CCamera(const bool _kbIsPerspective, glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a camera whose view frustrum is set using the window's width and height values as well as the given position and rotation. 
	/// </summary>
	/// <param name="_kbIsPerspective:">Is the camera perspective or orthographic?</param>
	/// <param name="_v3fPosition:">The starting position of the camera.</param>
	/// <param name="_v3fRotation:">The starting rotation of the camera.</param>
	CCamera(const bool _kbIsPerspective, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

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
	void Render(GLuint _uiProgram, CShape* _poShape);

	/// <summary>
	/// Sets the target position of the camera.
	/// </summary>
	/// <param name="_v3fTargetPosition:">The target position.</param>
	void SetTargetPosition(glm::vec3 _v3fTargetPosition);

	//glm::mat4* GetViewMatrix();

	//glm::mat4* GetProjectionMatrix();

	/// <summary>
	/// Returns the camera's transform.
	/// </summary>
	/// <returns>The camera's transform.</returns>
	CTransform* GetTransform();

	void SetProjectionSpace(bool _bIsPerspective, std::vector<CShape*>* _poVecShapePtrs);

	/// <summary>
	/// Returns the camera's projection space.
	/// </summary>
	/// <returns>True for perspective, false for orthographic.</returns>
	bool GetProjectionSpace();


private:
	//The camera's transform.
	CTransform m_oTransform;

	//The camera's projection space. True for perspective, false for orthographic.
	bool m_bIsPerspective;

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
	void CameraSetup();
};