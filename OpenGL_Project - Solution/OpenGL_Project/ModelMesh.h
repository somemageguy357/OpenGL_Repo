/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ModelMesh.h
Description : Mesh class for a model object. Sets up the vertex data using an obj loader.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Mesh.h"
#include <string>

class CModelMesh : public CMesh
{
public:
	CModelMesh(std::string _sFilePath);
	~CModelMesh();

protected:
	GLuint m_uiDrawCount = 0;
	int m_iDrawType = 0;
};