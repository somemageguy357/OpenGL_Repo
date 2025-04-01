#pragma once
#include "Shape.h"
#include "Texture.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CCamera : public CTransform
{
public:
	CCamera() = delete;
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight);
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition);
	CCamera(const int _kiWindowWidth, const int _kiWindowHeight, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	~CCamera();

	void Update();

	void Render(GLuint _uiProgram, CShape* _poShape);

	void SetTargetPosition(glm::vec3 _v3fTargetPosition);

	//glm::mat4* GetViewMatrix();

	//glm::mat4* GetProjectionMatrix();


private:
	glm::vec3 m_v3fCamForwardDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_v3fTargetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_v3fCamUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
			  
	glm::mat4 m_matView;
	glm::mat4 m_matProjection;

	void CameraSetup(const int _kiWindowWidth, const int _kiWindowHeight);
};