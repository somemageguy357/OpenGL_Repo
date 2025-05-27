/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Quad.h
Description : Deriving class of CObject. Contains the quad's vertex data, rendering object data, and textures.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Object.h"

// Deriving class of CObject. Contains the quad's vertex data, rendering object data, and textures.
class CQuad : public CObject
{
public:
	/// <summary>
	/// Creates a quad with default transform data. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CQuad();

	/// <summary>
	/// Creates a quad with the given position value. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) to their 
	/// default values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	CQuad(glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a quad with the given position and rotation values. Sets scale (1.0f, 1.0f, 1.0f) to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	/// <param name="_v3fRotation:">The starting rotation of the quad.</param>
	CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Creates a quad with the given transform values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	/// <param name="_v3fRotation:">The starting rotation of the quad.</param>
	/// <param name="_v3fScale:">The starting scale of the quad.</param>
	CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	~CQuad();

	void Render(CSkybox* _poSkybox, CCamera* _poCamera) override;

	/// <summary>
	/// Returns the vector of floats containing vertex position and colour data.
	/// </summary>
	/// <returns>The vector of floats containing vertex position and colour data.</returns>
	std::vector<float>* GetVertexData();

	/// <summary>
	/// Returns the vector of uints containing the vertex joints of the tris that make up the Object.
	/// </summary>
	/// <returns>The vector of uints containing the vertex joints of the tris that make up the Object.</returns>
	std::vector<unsigned int>* GetTriIndices();

private:

protected:
	GLuint m_uiVAO = 0;

	//Positions, colours, and texture coordinates of the mesh's vertices.
	std::vector<float> m_oVecVertexData;

	//Indices of the vertices for the triangles that make up the mesh.
	std::vector<unsigned int> m_oVecTriIndices;

	//Wraps the generative functions of the quad. Called from the quad's constructors.
	void ShapeSetup();

	//Generates the default vertex data of the quad.
	void GenerateVertexData();

	//Generates the default tri indice data of the quad.
	void GenerateTriIndices();

	//Generates the quad's render data (buffers, vertex pointers, etc).
	void GenerateShape();
};