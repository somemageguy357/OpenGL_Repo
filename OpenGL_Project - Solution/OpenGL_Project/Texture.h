#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <string>

class CTexture
{
public:
	CTexture() = delete;
	CTexture(std::string _sFilePath);
	~CTexture();

	GLuint GetTexture();

private:
	GLuint uiTexture = 0;
};