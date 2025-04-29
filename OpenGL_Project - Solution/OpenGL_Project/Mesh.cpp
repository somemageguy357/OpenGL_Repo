#include "Mesh.h"

CMesh::CMesh() {}

CMesh::~CMesh() {}

GLuint* CMesh::GetVAO()
{
	return &m_uiVAO;
}

std::vector<float> CMesh::GetVertexData()
{
	return m_oVecVertexData;
}

std::vector<unsigned int> CMesh::GetTriIndices()
{
	return m_oVecTriIndices;
}