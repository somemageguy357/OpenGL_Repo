#pragma once
#include "ComponentBehaviour.h"
#include <glm.hpp>

class CCameraBasedMovement : public CComponentBehaviour
{
public:
	CCameraBasedMovement() {};
	~CCameraBasedMovement() {};

	void Update(CShape* _poShape);

private:
	glm::vec3 m_v3fMoveDir = { 0.0f, 0.0f, 0.0f };
	float m_fMoveSpeed = 5.0f;
};