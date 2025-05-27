/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Object.cpp
Description : Contains function definitions for Object.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Object.h"
#include <iostream>

CObject::CObject() {}

CObject::CObject(glm::vec3 _v3fPosition)
{
	m_oTransform = CTransform(_v3fPosition);
}

CObject::CObject(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
{
	m_oTransform = CTransform(_v3fPosition, _v3fRotation);
}

CObject::CObject(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
{
	m_oTransform = CTransform(_v3fPosition, _v3fRotation, _v3fScale);
}

CObject::~CObject() {}

CTransform* CObject::GetTransform()
{
	return &m_oTransform;
}

CMesh* CObject::GetMesh()
{
	return m_poMesh;
}

void CObject::AddTexture(std::string _sTextureFilePath)
{
	m_oVecTextureIDs.push_back(CTextureManager::GetTexture(_sTextureFilePath));
}

std::vector<GLuint> CObject::GetTextureIDs()
{
	return m_oVecTextureIDs;
}

void CObject::BindTextures(GLuint _uiProgram)
{
	for (int i = 0; i < m_oVecTextureIDs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_oVecTextureIDs[i]);
		glUniform1i(glGetUniformLocation(_uiProgram, std::string("oTexture" + std::to_string(i)).c_str()), i);
	}
}

void CObject::AddComponentBehaviour(CComponentBehaviour* _poComponentBehaviour)
{
	m_oVecComponentBehaviourPtrs.push_back(_poComponentBehaviour);
}

void CObject::Update()
{
	for (size_t i = 0; i < m_oVecComponentBehaviourPtrs.size(); i++)
	{
		m_oVecComponentBehaviourPtrs[i]->Update(&m_oTransform);
	}
}