#include "Math.h"

glm::vec3 CMath::Normalize(const glm::vec3 _v3fVector)
{
	float fMag = sqrt(pow(_v3fVector.x, 2) + pow(_v3fVector.y, 2) + pow(_v3fVector.z, 2));

	if (fMag == 0)
	{
		return { 0.0f, 0.0f, 0.0f };
	}

	glm::vec3 v3fNormalizedVector = _v3fVector / fMag;

	return v3fNormalizedVector;
}