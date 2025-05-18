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
	//Control/movement mode for the camera.
	enum class ECameraMode
	{
		Free,
		Orbital,
	};

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
	/// Checks for movement input.
	/// </summary>
	void Update();

	/// <summary>
	/// Sets the target position of the camera.
	/// </summary>
	/// <param name="_v3fTargetPosition:">The target position.</param>
	void SetTargetPosition(glm::vec3 _v3fTargetPosition);

	/// <summary>
	/// Returns the camera's transform.
	/// </summary>
	/// <returns>The camera's transform.</returns>
	CTransform* GetTransform();

	/// <summary>
	/// Sets the projection space of the camera. Adjusts the scale multiplier of all objects in the given vector
	/// to match the change between perspective and orthographic projection spaces.
	/// </summary>
	/// <param name="_bIsPerspective:">Sets the projection space to perspective if true, orthographic if false.</param>
	/// <param name="_poVecShapePtrs:">Vector containing all shapes that will have their transforms adjusted.</param>
	void SetProjectionSpace(bool _bIsPerspective, std::vector<CShape*>* _poVecShapePtrs);

	/// <summary>
	/// Returns the camera's projection space.
	/// </summary>
	/// <returns>True for perspective, false for orthographic.</returns>
	bool GetProjectionSpace();

	/// <summary>
	/// Sets the camera control mode of the camera.
	/// </summary>
	/// <param name="_eCameraMode:">The camera control mode to change to.</param>
	void SetCameraMode(ECameraMode _eCameraMode);

	static CCamera* GetMainCamera();

	glm::mat4* GetViewMatrix();

	glm::mat4* GetProjectionMatrix();

	glm::vec3* GetForwardDirection();

private:
	static CCamera* m_poMainCamera;

	//The camera's transform.
	CTransform m_oTransform;

	//The camera's projection space. True for perspective, false for orthographic.
	bool m_bIsPerspective;

	//The mode of the camera (free, orbital, etc).
	ECameraMode m_eCameraMode;

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

	//Free camera values.
	float m_fPrevMouseX = 0.0f;
	float m_fPrevMouseY = 0.0f;
	float m_fYaw = 0.0f;
	float m_fPitch = 0.0f;
	float m_fOffsetX = 0.0f;
	float m_fOffsetY = 0.0f;

	//Orbital camera values.
	float m_fOrbitAngle = 0.0f;
	float m_fOrbitRadius = 10.0f;
	float m_fOrbitHeight = 3.0f;
	float m_fOrbitMoveSpeed = 0.5f;

	//Sets up the camera's projection matrix depending on the current projection space. Called from the constructors.
	void CameraSetup();

	//Runs the controls for the camera's free cam mode.
	void FreeCamControls();

	//Runs the controls for the camera's orbital cam mode.
	void OrbitalCamControls();

	//Used to get the input axis for the orbital cam control mode.
	int TriBool();
};