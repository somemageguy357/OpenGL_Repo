/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Hexagon.h
Description : Inheriting from Shape.h: sets up the shape with hexagon vertex data.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Shape.h"

/// <summary>
/// Holds information regarding a hexagon's position, rotation, scale, vertex positions, vertex colours, and VAO, VBO, and EBO.
/// </summary>
class CHexagon : public CShape
{
public:
	CHexagon();
	CHexagon(glm::vec3 _v3fPosition);
	CHexagon(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	CHexagon(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);
	~CHexagon();

private:
	void ShapeSetup() override;

	void SetVertexData() override;

	void SetTriIndices() override;
};