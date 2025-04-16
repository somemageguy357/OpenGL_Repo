#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

class CMath
{
public:
	static glm::vec3 Normalize(const glm::vec3 _v3fVector);

private:
	CMath() {};
	~CMath() {};
};