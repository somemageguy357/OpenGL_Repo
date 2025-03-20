/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Shape.h
Description : Base class for all shape types. Contains transform and vertex data for the shape.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

/// <summary>
/// Contains 3 float values (x, y, z).
/// </summary>
struct TVector3f
{
	float fX = 0.0f;
	float fY = 0.0f;
	float fZ = 0.0f;

	//Constructor for creating new TVector3fs.
	TVector3f(float _fX, float _fY, float _fZ)
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
	}

	TVector3f operator+=(TVector3f _rhs)
	{
		this->fX += _rhs.fX;
		this->fY += _rhs.fY;
		this->fZ += _rhs.fZ;

		return *this;
	}
}; 

class CShape
{
public:
	CShape();
	CShape(TVector3f _v3fPosition);
	CShape(TVector3f _v3fPosition, TVector3f _v3fRotation);
	CShape(TVector3f _v3fPosition, TVector3f _v3fRotation, TVector3f _v3fScale);
	~CShape();

	/// <summary>
	/// Returns the shape's translation matrix.
	/// </summary>
	/// <returns>The shape's translation matrix.</returns>
	glm::mat4* GetTranslationMatrix();

	/// <summary>
	/// Returns the shape's rotation matrix.
	/// </summary>
	/// <returns>The shape's rotation matrix.</returns>
	glm::mat4* GetRotationMatrix();

	/// <summary>
	/// Returns the shape's scale matrix.
	/// </summary>
	/// <returns>The shape's scale matrix.</returns>
	glm::mat4* GetScaleMatrix();

	/// <summary>
	/// Sets the shape's current position to the position in the given value.
	/// </summary>
	/// <param name="_v3fNewPosition:">The new position the shape is to be set to.</param>
	void SetPosition(TVector3f _v3fNewPosition);

	/// <summary>
	/// Adds the position in the given value to the shape's current position.
	/// </summary>
	/// <param name="_v3fPositionChange:">The change in position to add to the shape.</param>
	void AddPosition(TVector3f _v3fPositionChange);

	/// <summary>
	/// Sets the shape's current rotation to the rotation in the given value in degrees.
	/// </summary>
	/// <param name="_v3fNewRotation:">The new rotation the shape is to be set to in degrees.</param>
	void SetRotation(TVector3f _v3fNewRotation);

	/// <summary>
	/// Adds the rotation of _fRotationDegrees to the shape's current rotation in degrees. The axes of rotation
	/// is supplied in _v3fRotationAxes.
	/// </summary>
	/// <param name="_fRotationDegrees:">The change in rotation to add to the shape in degrees.</param>
	/// <param name="_v3fRotationAxes:">The axes that the change in rotation is to be applied to.</param>
	void AddRotation(float _fRotationDegrees, TVector3f _v3fRotationAxes);

	/// <summary>
	/// Sets the shape's current scale to the scale in the given vector3 value. Allows for differences in axes.
	/// </summary>
	/// <param name="_v3fNewScale:">The new scale the shape is to be set to.</param>
	void SetScale(TVector3f _v3fNewScale);

	/// <summary>
	/// Sets the shape's current scale to the scale in the given value. Affects all axes.
	/// </summary>
	/// <param name="_fNewScale:">The new scale the shape is to be set to.</param>
	void SetScale(float _fNewScale);

	/// <summary>
	/// Adds the scale in the given value to the shape's current scale.
	/// </summary>
	/// <param name="_v3fScaleChange:">The change in scale to add to the shape.</param>
	void AddScale(TVector3f _v3fScaleChange);

	/// <summary>
	/// Returns the address of the shape's VBO.
	/// </summary>
	/// <returns>The shape's VBO.</returns>
	GLuint* GetVBO();

	/// <summary>
	/// Returns the address of the shape's VAO.
	/// </summary>
	/// <returns>The shape's VAO.</returns>
	GLuint* GetVAO();

	/// <summary>
	/// Returns the address of the shape's EBO.
	/// </summary>
	/// <returns>The shape's EBO.</returns>
	GLuint* GetEBO();

	//virtual void SetVertexPositions(std::vector<TVector3f> _v3fVertexPositions) = 0;

	//virtual void SetVertexColours(std::vector<TVector3f> _v3fColours) = 0;

	/// <summary>
	/// Returns the vector of floats containing vertex position and colour data.
	/// </summary>
	/// <returns>The vector of floats containing vertex position and colour data.</returns>
	std::vector<float> GetVertexData();

	/// <summary>
	/// Returns the vector of uints containing the vertex joints of the tris that make up the quad.
	/// </summary>
	/// <returns>The vector of uints containing the vertex joints of the tris that make up the quad.</returns>
	std::vector<unsigned int> GetTriIndices();

protected:
	//Positions and colours of the shapes's vertices.
	std::vector<float> m_fVecVertexData;

	//Indices of the vertices for the triangles that make up the shape.
	std::vector<unsigned int> m_uiVecTriIndices;

	//Position of the shape.
	TVector3f m_v3fPosition = { 0.0f, 0.0f, 0.0f };

	//Rotation of the shape.
	TVector3f m_v3fRotation = { 0.0f, 0.0f, 0.0f };

	//Scale of the shape.
	TVector3f m_v3fScale = { 1.0f, 1.0f, 1.0f };

	//The shape's translation matrix.
	glm::mat4 m_matTranslation = glm::mat4(1.0f);

	//The shape's rotation matrix.
	glm::mat4 m_matRotation = glm::mat4(1.0f);

	//The shape's scale matrix.
	glm::mat4 m_matScale = glm::mat4(1.0f);

	//The shape's VBO.
	GLuint m_uiVBO = 0;

	//The shape's VAO.
	GLuint m_uiVAO = 0;

	//The shape's EBO.
	GLuint m_uiEBO = 0;

	virtual void ShapeSetup() = 0;

	virtual void SetVertexData() = 0;

	virtual void SetTriIndices() = 0;
};