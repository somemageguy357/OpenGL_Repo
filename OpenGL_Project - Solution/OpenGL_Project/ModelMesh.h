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