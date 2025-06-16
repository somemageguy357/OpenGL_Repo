#pragma once

// Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class ShaderLoader
{
	
public:
	enum class EShaderType
	{
		Unlit,
		Lit,
		Reflective,
		Skybox,
	};

	/// <summary>
	/// Used for model rendering. Lets the rendering process know if the model should be taking reflections and lighting into
	/// consideration, as well as providing it with the GLuint program ID.
	/// </summary>
	struct ShaderProgram
	{
		GLuint uiID;
		bool bRenderReflections = false;
		bool bRenderLighting = false;

		ShaderProgram() = delete;

		ShaderProgram(GLuint _uiID, ShaderLoader::EShaderType _eShaderType)
		{
			uiID = _uiID;
			
			if (_eShaderType == EShaderType::Lit)
			{
				bRenderLighting = true;
			}

			else if (_eShaderType == EShaderType::Reflective)
			{
				bRenderLighting = true;
				bRenderReflections = true;
			}
		}
	};

	static ShaderProgram* CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename, EShaderType _eShaderType);

private:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char *filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
