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
#include <iostream>

CShape::CShape() {}

CShape::CShape(glm::vec3 _v3fPosition)
{
	m_oTransform = CTransform(_v3fPosition);
}

CShape::CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
{
	m_oTransform = CTransform(_v3fPosition, _v3fRotation);
}

CShape::CShape(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
{
	m_oTransform = CTransform(_v3fPosition, _v3fRotation, _v3fScale);
}

CShape::~CShape() {}

CTransform* CShape::GetTransform()
{
	return &m_oTransform;
}

CMesh* CShape::GetMesh()
{
	return m_poMesh;
}

void CShape::AddTexture(CTexture* _poTexture)
{
	m_oVecTexturePtrs.push_back(_poTexture);

	if (_poTexture->GetAnimated() == true)
	{
		SetNewQuadTexCoords(*_poTexture->GetCurrentFrameTexCoords());
	}
}

std::vector<CTexture*> CShape::GetTextures()
{
	return m_oVecTexturePtrs;
}

void CShape::BindTextures(GLuint _uiProgram)
{
	for (int i = 0; i < m_oVecTexturePtrs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_oVecTexturePtrs[i]->GetTexture());
		glUniform1i(glGetUniformLocation(_uiProgram, std::string("oTexture" + std::to_string(i)).c_str()), i);

		//If the texture is animated: change the quads's texture coordinates to match the right frame to display.
		if (m_oVecTexturePtrs[i]->GetAnimated() == true && m_oVecTexturePtrs[i]->GetNextFrameReady() == true)
		{
			SetNewQuadTexCoords(*m_oVecTexturePtrs[i]->GetCurrentFrameTexCoords());
		}
	}
}

void CShape::SetNewQuadTexCoords(std::vector<float> _fVecNewTexCoords)
{
	//If the deriving class is not a CQuad (the only class that overrides this function), this will instead run.
	std::cout << "Attempt to set new texture coordinates for a shape failed: the shape is not a quad." << std::endl;
}

void CShape::AddComponentBehaviour(CComponentBehaviour* _poComponentBehaviour)
{
	m_oVecComponentBehaviourPtrs.push_back(_poComponentBehaviour);
}

void CShape::Update()
{
	for (size_t i = 0; i < m_oVecComponentBehaviourPtrs.size(); i++)
	{
		m_oVecComponentBehaviourPtrs[i]->Update(&m_oTransform);
	}
}