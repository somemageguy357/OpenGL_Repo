/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Cube.cpp
Description : Contains function definitions for Cube.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Cube.h"
#include "CubeMesh.h"

CCube::CCube() : CShape()
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition) : CShape(_v3fPosition)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	m_poMesh = CCubeMesh::GetInstance();
}

CCube::~CCube() {}