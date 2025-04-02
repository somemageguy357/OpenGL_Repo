/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Transform.cpp
Description : Contains function definitions for Transform.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Transform.h"

CTransform::CTransform() {}

CTransform::CTransform(glm::vec3 _v3fPosition)
{
	SetPosition(_v3fPosition);
}

CTransform::CTransform(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
{
	SetPosition(_v3fPosition);
	SetRotation(_v3fRotation);
}

CTransform::CTransform(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
{
	SetPosition(_v3fPosition);
	SetRotation(_v3fRotation);
	SetScale(_v3fScale);
}

CTransform::~CTransform() {}

glm::mat4* CTransform::GetTranslationMatrix()
{
	return &m_matTranslation;
}

glm::mat4* CTransform::GetRotationMatrix()
{
	return &m_matRotation;
}

glm::mat4* CTransform::GetScaleMatrix()
{
	return &m_matScale;
}

glm::mat4* CTransform::GetModelMatrix()
{
	m_matModel = m_matTranslation * m_matRotation * m_matScale;
	return &m_matModel;
}

void CTransform::SetPosition(glm::vec3 _v3fNewPosition)
{
	m_v3fPosition = _v3fNewPosition;

	m_matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(m_v3fPosition.x, m_v3fPosition.y, m_v3fPosition.z));
}

void CTransform::AddPosition(glm::vec3 _v3fPositionChange)
{
	m_v3fPosition += _v3fPositionChange;

	m_matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(m_v3fPosition.x, m_v3fPosition.y, m_v3fPosition.z));
}

glm::vec3* CTransform::GetPosition()
{
	return &m_v3fPosition;
}

void CTransform::SetRotation(glm::vec3 _v3fNewRotation)
{
	m_v3fRotation = _v3fNewRotation;

	m_matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_v3fNewRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void CTransform::AddRotation(float _fRotationDegrees, glm::vec3 _v3fRotationAxes)
{
	m_v3fRotation += glm::vec3(_v3fRotationAxes.x * _fRotationDegrees, _v3fRotationAxes.y * _fRotationDegrees, _v3fRotationAxes.z * _fRotationDegrees);

	m_matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.x + _fRotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.y + _fRotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_v3fRotation.z + _fRotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3* CTransform::GetRotation()
{
	return &m_v3fRotation;
}

void CTransform::SetScale(glm::vec3 _v3fNewScale)
{
	m_v3fScale = _v3fNewScale;

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.x, m_v3fScale.y, m_v3fScale.z));
}

void CTransform::SetScale(float _fNewScale)
{
	m_v3fScale = glm::vec3(_fNewScale, _fNewScale, _fNewScale);

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.x, m_v3fScale.y, m_v3fScale.z));
}

void CTransform::AddScale(glm::vec3 _v3fScaleChange)
{
	m_v3fScale += _v3fScaleChange;

	m_matScale = glm::scale(glm::mat4(1.0f), glm::vec3(m_v3fScale.x, m_v3fScale.y, m_v3fScale.z));
}

glm::vec3* CTransform::GetScale()
{
	return &m_v3fScale;
}