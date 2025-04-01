/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Shape.cpp
Description : Contains function definitions for Shape.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Shape.h"

CShape::CShape() : CTransform::CTransform () {}

CShape::CShape(glm::vec3 _v3fPosition) : CTransform(_v3fPosition) {}

CShape::CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CTransform(_v3fPosition, _v3fRotation) {}

CShape::CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CTransform(_v3fPosition, _v3fRotation, _v3fScale) {}

CShape::~CShape() {}

GLuint* CShape::GetVBO()
{
	return &m_uiVBO;
}

GLuint* CShape::GetVAO()
{
	return &m_uiVAO;
}

GLuint* CShape::GetEBO()
{
	return &m_uiEBO;
}

std::vector<float> CShape::GetVertexData()
{
	return m_fVecVertexData;
}

std::vector <unsigned int> CShape::GetTriIndices()
{
	return m_uiVecTriIndices;
}

void CShape::AddTexture(CTexture* _poTexture)
{
	m_poVecTextures.push_back(_poTexture);
}

std::vector<CTexture*> CShape::GetTextures()
{
	return m_poVecTextures;
}

void CShape::BindTextures(GLuint _uiProgram)
{
	for (int i = 0; i < m_poVecTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_poVecTextures[i]->GetTexture());
		glUniform1i(glGetUniformLocation(_uiProgram, std::string("oTexture" + std::to_string(i)).c_str()), i);
	}
}