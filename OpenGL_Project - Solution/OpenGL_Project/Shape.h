/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Shape.h
Description : Base class for all shape types. Contains vertex, rendering object, and texture data for the shape as well as its transform.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"

#include <vector>

/// <summary>
/// Base class for all 2D and 3D shape types. Contains a shape's vertex data, rendering object data, and textures
/// as well as its transform. Objects of this type specifically cannot be created.
/// </summary>
class CShape
{
public:
	struct VertexStandard
	{
		glm::vec3 v3fPosition;
		glm::vec3 v3fColour;
		glm::vec2 v2fTexCoord;

		VertexStandard()
		{
			v3fPosition = { 0.0f, 0.0f, 0.0f };
			v3fColour = { 0.0f, 0.0f, 0.0f };
			v2fTexCoord = { 0.0f, 0.0f };
		}

		VertexStandard(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, glm::vec2 _v2fTexCoord)
		{
			v3fPosition = _v3fPosition;
			v3fColour = _v3fColour;
			v2fTexCoord = _v2fTexCoord;
		}
	};

	~CShape();

	/// <summary>
	/// Returns the shape's transform.
	/// </summary>
	/// <returns>The shape's transform.</returns>
	CTransform* GetTransform();

	CMesh* GetMesh();

	/// <summary>
	/// Adds a CTexture to the vector containing this shape's CTextures.
	/// </summary>
	/// <param name="_poTexture:">The pointer to the CTexture that is to be added.</param>
	void AddTexture(CTexture* _poTexture);

	/// <summary>
	/// Returns the vector containing all of this shape's CTextures.
	/// </summary>
	/// <returns>The vector containing all of this shape's CTextures.</returns>
	std::vector<CTexture*> GetTextures();

	/// <summary>
	/// Binds all of the shape's textures to be used for rendering. Should only be done during the rendering stage of the program.
	/// </summary>
	/// <param name="_uiProgram:">The program that the textures are to use.</param>
	void BindTextures(GLuint _uiProgram);

	/// <summary>
	/// Sets the texture coordinate portion of the shape's vertex data to the given values. The given vector MUST contain 8
	/// elements. This function may be called for any shape type but only works with shapes of type: CQuad.
	/// </summary>
	/// <param name="_fVecNewTexCoords:">The vector containing the new texture coordinate data.</param>
	virtual void SetNewQuadTexCoords(std::vector<float> _fVecNewTexCoords);

protected:
	//The shape's transform.
	CTransform m_oTransform;

	CMesh* m_poMesh = nullptr;

	/// <summary>
	/// Creates a shape with default transform data. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CShape();

	/// <summary>
	/// Creates a shape with the given position value. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) to their 
	/// default values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the shape.</param>
	CShape(glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a shape with the given position and rotation values. Sets scale (1.0f, 1.0f, 1.0f) to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the shape.</param>
	/// <param name="_v3fRotation:">The starting rotation of the shape.</param>
	CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Creates a shape with the given transform values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the shape.</param>
	/// <param name="_v3fRotation:">The starting rotation of the shape.</param>
	/// <param name="_v3fScale:">The starting scale of the shape.</param>
	CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

private:
	//The vector containing the shape's CTextures.
	std::vector<CTexture*> m_oVecTexturePtrs;
};