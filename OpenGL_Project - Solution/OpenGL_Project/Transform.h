/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Transform.h
Description : Contains matrices and vectors for an object's transform values.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Contains matrices and vectors for an object's transform values.
class CTransform
{
public:
	/// <summary>
	/// Sets the transform of the object with default values. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). 
	/// Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CTransform();

	/// <summary>
	/// Sets the transform of the object with the given position. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) 
	/// to their default values.
	/// </summary>
	/// <param name="_v3fPosition:">Starting position of the transform.</param>
	CTransform(glm::vec3 _v3fPosition);

	/// <summary>
	/// Sets the transform of the object with the given position and rotation. Sets scale (1.0f, 1.0f, 1.0f) 
	/// to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">Starting position of the transform.</param>
	/// <param name="_v3fRotation:">Starting rotation of the transform.</param>
	CTransform(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Sets the transform of the object with the given position, rotation, and scale values.
	/// </summary>
	/// <param name="_v3fPosition:">Starting position of the transform.</param>
	/// <param name="_v3fRotation:">Starting rotation of the transform.</param>
	/// <param name="_v3fScale:">Starting scale of the transform.</param>
	CTransform(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	~CTransform();

	/// <summary>
	/// Returns the transform's translation matrix.
	/// </summary>
	/// <returns>The transform's translation matrix.</returns>
	glm::mat4* GetTranslationMatrix();

	/// <summary>
	/// Returns the transform's rotation matrix.
	/// </summary>
	/// <returns>The transform's rotation matrix.</returns>
	glm::mat4* GetRotationMatrix();

	/// <summary>
	/// Returns the transform's scale matrix.
	/// </summary>
	/// <returns>The transform's scale matrix.</returns>
	glm::mat4* GetScaleMatrix();

	/// <summary>
	/// Returns the transform's model matrix.
	/// </summary>
	/// <returns>The transform's model matrix.</returns>
	glm::mat4* GetModelMatrix();

	/// <summary>
	/// Sets the transform's current position to the position in the given value.
	/// </summary>
	/// <param name="_v3fNewPosition:">The new position the transform is to be set to.</param>
	void SetPosition(glm::vec3 _v3fNewPosition);

	/// <summary>
	/// Adds the position in the given value to the transform's current position.
	/// </summary>
	/// <param name="_v3fPositionChange:">The change in position to add to the transform.</param>
	void AddPosition(glm::vec3 _v3fPositionChange);

	/// <summary>
	/// Returns the Vector3 positon of the transform.
	/// </summary>
	/// <returns>The Vector3 positon of the transform.</returns>
	glm::vec3* GetPosition();

	/// <summary>
	/// Sets the transform's current rotation to the rotation in the given value in degrees.
	/// </summary>
	/// <param name="_v3fNewRotation:">The new rotation the transform is to be set to in degrees.</param>
	void SetRotation(glm::vec3 _v3fNewRotation);

	/// <summary>
	/// Adds the rotation of _fRotationDegrees to the transform's current rotation in degrees. The axes of rotation
	/// is supplied in _v3fRotationAxes.
	/// </summary>
	/// <param name="_fRotationDegrees:">The change in rotation to add to the transform in degrees.</param>
	/// <param name="_v3fRotationAxes:">The axes that the change in rotation is to be applied to.</param>
	void AddRotation(float _fRotationDegrees, glm::vec3 _v3fRotationAxes);

	/// <summary>
	/// Returns the Vector3 rotation of the transform.
	/// </summary>
	/// <returns>The Vector3 rotation of the transform.</returns>
	glm::vec3* GetRotation();

	/// <summary>
	/// Sets the transform's current scale to the scale in the given vector3 value. Allows for differences in axes.
	/// </summary>
	/// <param name="_v3fNewScale:">The new scale the transform is to be set to.</param>
	void SetScale(glm::vec3 _v3fNewScale);

	/// <summary>
	/// Sets the transform's current scale to the scale in the given value. Affects all axes.
	/// </summary>
	/// <param name="_fNewScale:">The new scale the transform is to be set to.</param>
	void SetScale(float _fNewScale);

	/// <summary>
	/// Adds the scale in the given value to the transform's current scale.
	/// </summary>
	/// <param name="_v3fScaleChange:">The change in scale to add to the transform.</param>
	void AddScale(glm::vec3 _v3fScaleChange);

	/// <summary>
	/// Returns the Vector3 scale of the transform.
	/// </summary>
	/// <returns>The Vector3 scale of the transform.</returns>
	glm::vec3* GetScale();

	/// <summary>
	/// Sets the multipler for the transform's scale and position. Used for adjusting the visual scale and position of the object based 
	/// on the camera's projection space (perspective vs orthographic). This also updates the transform's current position and
	/// scale matrices using this value.
	/// </summary>
	/// <param name="_fScaleMultiplier:">The multiplier for the transform's scale and position.</param>
	void SetScaleMultiplier(float _fScaleMultiplier);

private:
	//Position of the transform.
	glm::vec3 m_v3fPosition = { 0.0f, 0.0f, 0.0f };

	//Rotation of the transform.
	glm::vec3 m_v3fRotation = { 0.0f, 0.0f, 0.0f };

	//Scale of the transform.
	glm::vec3 m_v3fScale = { 1.0f, 1.0f, 1.0f };

	//How much the scale is multiplied by. Used for camera projection spaces.
	float m_fScaleMultiplier = 1.0f;

	//The transform's translation matrix.
	glm::mat4 m_matTranslation = glm::mat4(1.0f);

	//The transform's rotation matrix.
	glm::mat4 m_matRotation = glm::mat4(1.0f);

	//The transform's scale matrix.
	glm::mat4 m_matScale = glm::mat4(1.0f);

	//The transform's model matrix.
	glm::mat4 m_matModel = glm::mat4(1.0f);
};