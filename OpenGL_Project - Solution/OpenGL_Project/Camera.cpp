#include "Camera.h"

CCamera::CCamera(const int _kiWindowWidth, const int _kiWindowHeight) : CTransform()
{
	CameraSetup(_kiWindowWidth, _kiWindowHeight);
}

CCamera::CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition) : CTransform(_v3fPosition)
{
	CameraSetup(_kiWindowWidth, _kiWindowHeight);
}

CCamera::CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CTransform(_v3fPosition, _v3fRotation)
{
	CameraSetup(_kiWindowWidth, _kiWindowHeight);
}

CCamera::~CCamera() {}

void CCamera::Update()
{
	m_matView = glm::lookAt(m_v3fPosition, m_v3fPosition + m_v3fCamForwardDir, m_v3fCamUpDir); //Look at position.
	//matProjection = glm::ortho(-(float)_kiWindowWidth * 0.5f, (float)_kiWindowWidth * 0.5f, -(float)_kiWindowHeight * 0.5f, (float)_kiWindowHeight * 0.5f, 0.1f, 100.0f);
}

void CCamera::Render(GLuint _uiProgram, CShape* _poShape)
{
	glUseProgram(_uiProgram);

	glBindVertexArray(*_poShape->GetVAO());

	_poShape->BindTextures(_uiProgram);

	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*_poShape->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(m_matView));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(m_matProjection));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void CCamera::SetTargetPosition(glm::vec3 _v3fTargetPosition)
{
	m_v3fTargetPosition = _v3fTargetPosition;
}

//glm::mat4* CCamera::GetViewMatrix()
//{
//	return &matView;
//}
//
//glm::mat4* CCamera::GetProjectionMatrix()
//{
//	return &matProjection;
//}

void CCamera::CameraSetup(const int _kiWindowWidth, const int _kiWindowHeight)
{
	m_matView = glm::lookAt(m_v3fPosition, m_v3fPosition + m_v3fCamForwardDir, m_v3fCamUpDir); //Look at position.
	//matView = glm::lookAt(v3fCamPosition, v3fCamTargetPosition, v3fCamUpDir); //Look at target.

	m_matProjection = glm::ortho(-(float)_kiWindowWidth * 0.5f, (float)_kiWindowWidth * 0.5f, -(float)_kiWindowHeight * 0.5f, (float)_kiWindowHeight * 0.5f, 0.1f, 100.0f);
}