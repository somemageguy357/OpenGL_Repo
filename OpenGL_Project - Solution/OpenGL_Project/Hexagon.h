/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Hexagon.h
Description : Deriving class of CShape. Contains the hexagon's vertex data, rendering object data, and textures.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Shape.h"

// Deriving class of CShape. Contains the hexagon's vertex data, rendering object data, and textures.
class CHexagon : public CShape
{
public:
	/// <summary>
	/// Creates a hexagon with default transform data. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CHexagon();

	/// <summary>
	/// Creates a hexagon with the given position value. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) to their 
	/// default values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the hexagon.</param>
	CHexagon(glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a hexagon with the given position and rotation values. Sets scale (1.0f, 1.0f, 1.0f) to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the hexagon.</param>
	/// <param name="_v3fRotation:">The starting rotation of the hexagon.</param>
	CHexagon(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Creates a hexagon with the given transform values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the hexagon.</param>
	/// <param name="_v3fRotation:">The starting rotation of the hexagon.</param>
	/// <param name="_v3fScale:">The starting scale of the hexagon.</param>
	CHexagon(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	~CHexagon();

private:
	////Wraps the generative functions of the hexagon. Called from the hexagon's constructors.
	//void ShapeSetup() override;

	////Generates the default vertex data of the hexagon.
	//void GenerateVertexData() override;

	////Generates the default tri indice data of the hexagon.
	//void GenerateTriIndices() override;

	////Generates the hexagon's render data (buffers, vertex pointers, etc).
	//void GenerateShape() override;
};