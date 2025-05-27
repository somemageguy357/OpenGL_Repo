/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : CameraBasedMovement.h
Description : A component class that allows a transform to be moved based on the camera's direction vectors.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "ComponentBehaviour.h"

//Allows an object to be moved based on the camera's direction vectors.
class CCameraBasedMovement : public CComponentBehaviour
{
public:
	/// <summary>
	/// Stores the starting position of the transform.
	/// </summary>
	/// <param name="_v3fStartingPosition:">The starting position of the transform.</param>
	CCameraBasedMovement(glm::vec3 _v3fStartingPosition);

	~CCameraBasedMovement() {};

	/// <summary>
	/// Contains controls that moves the transform based on the camera's direction vectors.
	/// </summary>
	/// <param name="_poTransform"></param>
	void Update(CTransform* _poTransform);

private:
	glm::vec3 m_v3fStartingPosition = { 0.0f, 0.0f, 0.0f };

	glm::vec3 m_v3fMoveDir = { 0.0f, 0.0f, 0.0f };
	float m_fMoveSpeed = 5.0f;
};