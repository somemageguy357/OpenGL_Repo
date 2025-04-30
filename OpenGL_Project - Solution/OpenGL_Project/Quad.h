/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Quad.h
Description : Deriving class of CShape. Contains the quad's vertex data, rendering object data, and textures.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Shape.h"

// Deriving class of CShape. Contains the quad's vertex data, rendering object data, and textures.
class CQuad : public CShape
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

	void Render(GLuint _uiProgram) override;

	/// <summary>
	/// Sets the texture coordinate portion of the quad's vertex data to the given values. The given vector MUST contain 8
	/// elements.
	/// </summary>
	/// <param name="_fVecNewTexCoords:">The vector containing the new texture coordinate data.</param>
	void SetNewQuadTexCoords(std::vector<float> _fVecNewTexCoords) override;

private:
	////Wraps the generative functions of the quad. Called from the quad's constructors.
	//void ShapeSetup() override;

	////Generates the default vertex data of the quad.
	//void GenerateVertexData() override;

	////Generates the default tri indice data of the quad.
	//void GenerateTriIndices() override;

	////Generates the quad's render data (buffers, vertex pointers, etc).
	//void GenerateShape() override;
};