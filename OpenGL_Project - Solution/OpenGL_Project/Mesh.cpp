/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Mesh.cpp
Description : Contains function definitions for Mesh.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Mesh.h"

CMesh::CMesh() {}

CMesh::~CMesh() {}

GLuint* CMesh::GetVAO()
{
	return &m_uiVAO;
}

std::vector<float>* CMesh::GetVertexData()
{
	return &m_oVecVertexData;
}

std::vector<unsigned int>* CMesh::GetTriIndices()
{
	return &m_oVecTriIndices;
}