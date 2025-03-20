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

CShape::CShape() {}

CShape::CShape(TVector3f _v3fPosition)
{
	SetPosition(_v3fPosition);
}

CShape::CShape(TVector3f _v3fPosition, TVector3f _v3fRotation)
{
	SetPosition(_v3fPosition);
	SetRotation(_v3fRotation);
}

CShape::CShape(TVector3f _v3fPosition, TVector3f _v3fRotation, TVector3f _v3fScale)
{
	SetPosition(_v3fPosition);
	SetRotation(_v3fRotation);
	SetScale(_v3fScale);
}

CShape::~CShape() {}

//void CShape::SetVertexPositions(std::vector<TVector3f> _v3fVertexPositions)
//{
//	//std::cout << "Shape Vertices: " << std::endl;
//
//	for (size_t i = 0; i < 6; i++)
//	{
//		m_fVecVertexData[i * 6] = _v3fVertexPositions[i].fX;
//		m_fVecVertexData[(i * 6) + 1] = _v3fVertexPositions[i].fY;
//		m_fVecVertexData[(i * 6) + 2] = _v3fVertexPositions[i].fZ;
//
//		//std::cout << "[" << i << "]: (" << m_fVecVertexData[i * 6] << ", " << m_fVecVertexData[(i * 6) + 1] << ", " << m_fVecVertexData[(i * 6) + 2] << ")" << std::endl;
//	}
//
//	std::cout << std::endl;
//}
//
//void CShape::SetVertexColours(std::vector<TVector3f> _v3fColours)
//{
//	//std::cout << "Shape Colours: " << std::endl;
//
//	for (size_t i = 0; i < 6; i++)
//	{
//		m_fVecVertexData[(i * 6) + 3] = _v3fColours[i].fX;
//		m_fVecVertexData[(i * 6) + 4] = _v3fColours[i].fY;
//		m_fVecVertexData[(i * 6) + 5] = _v3fColours[i].fZ;
//
//		//std::cout << "[" << i << "]: (" << m_fVecVertexData[(i * 6) + 3] << ", " << m_fVecVertexData[(i * 6) + 4] << ", " << m_fVecVertexData[(i * 6) + 5] << ")" << std::endl;
//	}
//
//	std::cout << std::endl;
//}

glm::mat4* CShape::GetTranslationMatrix()
{
	return &m_matTranslation;
}

glm::mat4* CShape::GetRotationMatrix()
{
	return &m_matRotation;
}

glm::mat4* CShape::GetScaleMatrix()
{
	return &m_matScale;
}

void CShape::SetPosition(TVector3f _v3fNewPosition)
{
	m_v3fPosition = _v3fNewPosition;

	m_matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(m_v3fPosition.fX, m_v3fPosition.fY, m_v3fPosition.fZ));

	//std::cout << "New Position: (" << m_v3fPosition.fX << ", " << m_v3fPosition.fY << ", " << m_v3fPosition.fZ << ")" << std::endl;
}

void CShape::AddPosition(TVector3f _v3fPositionChange)
{
	m_v3fPosition += _v3fPositionChange;

	m_matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(m_v3fPosition.fX, m_v3fPosition.fY, m_v3fPosition.fZ));

	//std::cout << "New Position: (" << m_v3fPosition.fX << ", " << m_v3fPosition.fY << ", " << m_v3fPosition.fZ << ")" << std::endl;
}

void CShape::SetRotation(TVector3f _v3fNewRotation)
{
	m_v3fRotation = _v3fNewRotation;

	m_matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.fX), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.fY), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.fZ), glm::vec3(0.0f, 0.0f, 1.0f));

	//std::cout << "New Rotation: (" << m_v3fRotation.fX << ", " << m_v3fRotation.fY << ", " << m_v3fRotation.fZ << ")" << std::endl;
}

void CShape::AddRotation(float _fRotationDegrees, TVector3f _v3fRotationAxes)
{
	m_v3fRotation += TVector3f(_v3fRotationAxes.fX * _fRotationDegrees, _v3fRotationAxes.fY * _fRotationDegrees, _v3fRotationAxes.fZ * _fRotationDegrees);

	m_matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.fX + _fRotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.fY + _fRotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.fZ + _fRotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

	//std::cout << "New Rotation: (" << m_v3fRotation.fX << ", " << m_v3fRotation.fY << ", " << m_v3fRotation.fZ << ")" << std::endl;
}

void CShape::SetScale(TVector3f _v3fNewScale)
{
	m_v3fScale = _v3fNewScale;

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.fX, m_v3fScale.fY, m_v3fScale.fZ));

	//std::cout << "New Scale: (" << m_v3fScale.fX << ", " << m_v3fScale.fY << ", " << m_v3fScale.fZ << ")" << std::endl;
}

void CShape::SetScale(float _fNewScale)
{
	m_v3fScale = TVector3f(1.0f * _fNewScale, 1.0f * _fNewScale, 1.0f * _fNewScale);

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.fX, m_v3fScale.fY, m_v3fScale.fZ));

	//std::cout << "New Scale: (" << m_v3fScale.fX << ", " << m_v3fScale.fY << ", " << m_v3fScale.fZ << ")" << std::endl;
}

void CShape::AddScale(TVector3f _v3fScaleChange)
{
	m_v3fScale += _v3fScaleChange;

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.fX, m_v3fScale.fY, m_v3fScale.fZ));

	//std::cout << "New Scale: (" << m_v3fScale.fX << ", " << m_v3fScale.fY << ", " << m_v3fScale.fZ << ")" << std::endl;
}

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