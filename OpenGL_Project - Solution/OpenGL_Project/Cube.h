/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Cube.h
Description : Deriving class of CShape. Contains the cube's vertex data, rendering object data, and textures.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Shape.h"

// Deriving class of CShape. Contains the cube's vertex data, rendering object data, and textures.
class CCube : public CShape
{
public:
	/// <summary>
	/// Creates a quad with default transform data. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CCube();

	/// <summary>
	/// Creates a quad with the given position value. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) to their 
	/// default values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	CCube(glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a quad with the given position and rotation values. Sets scale (1.0f, 1.0f, 1.0f) to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	/// <param name="_v3fRotation:">The starting rotation of the quad.</param>
	CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Creates a quad with the given transform values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the quad.</param>
	/// <param name="_v3fRotation:">The starting rotation of the quad.</param>
	/// <param name="_v3fScale:">The starting scale of the quad.</param>
	CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	~CCube();
};