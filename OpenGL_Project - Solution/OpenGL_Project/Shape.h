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
#include "Transform.h"
#include "Texture.h"

#include <vector>

class CShape : public CTransform
{
public:
	CShape();
	CShape(glm::vec3 _v3fPosition);
	CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);
	~CShape();

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

	void AddTexture(CTexture* _poTexture);

	std::vector<CTexture*> GetTextures();

	void BindTextures(GLuint _uiProgram);

protected:
	//Positions and colours of the shapes's vertices.
	std::vector<float> m_fVecVertexData;

	//Indices of the vertices for the triangles that make up the shape.
	std::vector<unsigned int> m_uiVecTriIndices;

	//The shape's VBO.
	GLuint m_uiVBO = 0;

	//The shape's VAO.
	GLuint m_uiVAO = 0;

	//The shape's EBO.
	GLuint m_uiEBO = 0;

	virtual void ShapeSetup() = 0;

	virtual void SetVertexData() = 0;

	virtual void SetTriIndices() = 0;

private:
	std::vector<CTexture*> m_poVecTextures;
};