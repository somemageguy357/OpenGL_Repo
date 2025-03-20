/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : main.cpp
Description : Entry point for the program and contains the main program loop.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <string>

#include "ShaderLoader.h"
#include "Hexagon.h"
#include "Quad.h"

//------GLOBAL VARIABLES------
const int kiWindowWidth = 800;
const int kiWindowHeight = 800;

float fCurrentTime = 0.0f;
float fDeltaTime = 0.0f;

GLuint uiProgram = 0;
GLuint uiTexProgram = 0;

GLuint uiPotionTex = 0;

std::vector<CShape*> poVecShapes;

float fRotationSpeed = 45.0f;
//----------------------------

/// <summary>
/// Sets up the OpenGL framework and attempts to create the window that the program renders to.
/// </summary>
/// <returns>The window the program renders to, nullptr if the process fails.</returns>
GLFWwindow* InitializeGLSetup();

/// <summary>
/// Creates a shape and adds it to the vector containing them (poVecShapes).
/// </summary>
void CreateShape();

/// <summary>
/// Updates any transform changes made to any chosen objects.
/// </summary>
void Update();

/// <summary>
/// Renders all objects to the window and swaps the buffers.
/// </summary>
/// <param name="_poWindow:">The window that buffers are swapped to.</param>
void Render(GLFWwindow* _poWindow);

int main()
{
	bool bCloseProgram = false;
	GLFWwindow* poWindow = InitializeGLSetup();

	if (poWindow == nullptr)
	{
		bCloseProgram = true;
	}

	else
	{
		//-------------------------------------------Texture
		uiTexProgram = ShaderLoader::CreateProgram("Resources/Shaders/Texture.vert", "Resources/Shaders/Texture.frag");

		int iImageWidth;
		int iImageHeight;
		int iImageComponents;
		unsigned char* pucImageData = stbi_load("Resources/Textures/Run.png", &iImageWidth, &iImageHeight, &iImageComponents, 0);

		//Create and bind a new texture variable.
		glGenTextures(1, &uiPotionTex);
		glBindTexture(GL_TEXTURE_2D, uiPotionTex);

		//Check how many components the loaded image has (RGBA or RGB).
		GLint uiLoadedComponents = GL_RGBA;

		if (iImageComponents != 4)
		{
			uiLoadedComponents = GL_RGB;
		}

		//Populate the texture with image data.
		glTexImage2D(GL_TEXTURE_2D, 0, uiLoadedComponents, iImageWidth, iImageHeight, 0, uiLoadedComponents, GL_UNSIGNED_BYTE, pucImageData);

		//Generate the mipmaps, free the memory and unbind the texture.
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(pucImageData);
		glBindTexture(GL_TEXTURE_2D, 0);

		//--------------------------------------------------

		//uiProgram = ShaderLoader::CreateProgram("Resources/Shaders/Transform.vert", "Resources/Shaders/VertexColourFade.frag");

		for (int i = 0; i < 1; i++)
		{
			CreateShape();
		}

		//Reposition the shapes from their starting positions.
		//poVecShapes[0]->SetPosition({ 0.5f, 0.5f, 0.0f });
		//poVecShapes[1]->SetPosition({ -0.5f, -0.5f, 0.0f });
	}

	//Main loop.
	while (bCloseProgram == false && glfwWindowShouldClose(poWindow) == false)
	{
		Update();
		Render(poWindow);
	}

	//Clean up the program. Delete pointers and terminate the render window.
	for (int i = 0; i < poVecShapes.size(); i++)
	{
		delete poVecShapes[i];
	}

	poVecShapes.clear();

	glfwTerminate();
}

GLFWwindow* InitializeGLSetup()
{
	//Title of the window.
	std::string sWindowTitle = "Main Window (" + std::to_string(kiWindowWidth) + "x" + std::to_string(kiWindowHeight) + ")";

	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* poWindow = glfwCreateWindow(kiWindowWidth, kiWindowHeight, sWindowTitle.c_str(), NULL, NULL);

	//If the window fails to create: terminate it.
	if (poWindow == nullptr)
	{
		std::cout << "GLFW failed. Ending program..." << std::endl;
		system("pause");
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(poWindow);

	//Initializes GLEW and determines the success of the action. This must be done AFTER the GLFW window has been initialized and BEFORE
	//any gl function calls.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed. Ending program..." << std::endl;
		system("pause");
		glfwTerminate();
		return nullptr;
	}

	//Sets the colour of the window when the buffer is cleared. Must come after the window has been created.
	//Can be called again to change the colour.
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//Maps the range of the window size to NDC (Normalized Device Coordinates). Range is -1 to 1.
	//Needs to be called again if the window is resized.
	glViewport(0, 0, kiWindowWidth, kiWindowHeight);

	return poWindow;
}

void CreateShape()
{
	//CHexagon* poHexagon = new CHexagon();
	//poVecShapes.push_back(poHexagon);

	CQuad* poQuad = new CQuad();
	poVecShapes.push_back(poQuad);
}

void Update()
{
	glfwPollEvents();
	fDeltaTime = (float)glfwGetTime() - fCurrentTime;
	fCurrentTime = (float)glfwGetTime();

	//Cycles through each shape and updates their rotation and scale.
	for (int i = 0; i < poVecShapes.size(); i++)
	{
		//poVecShapes[i]->AddRotation(fRotationSpeed * fDeltaTime, { 0.0f, 0.0f, 1.0f });
		//poVecShapes[i]->SetScale((sin(fCurrentTime) * 0.5f) + 1.0f);
	}
}

void Render(GLFWwindow* _poWindow)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(uiTexProgram);

	//Activate and bind the texture.
	glActiveTexture(GL_TEXTURE0); //<-- num must match below.
	glBindTexture(GL_TEXTURE_2D, uiPotionTex);
	glUniform1i(glGetUniformLocation(uiTexProgram, "oTexture0"), 0); //<- num must match above.

	////Binds the VAO of the first shape only.
	//glBindVertexArray(*poVecShapes[0]->GetVAO());

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glUseProgram(uiProgram);

	//GLint iCurrentTimeLocation = glGetUniformLocation(uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, fCurrentTime);

	//Binds the VAO of the first shape only.
	glBindVertexArray(*poVecShapes[0]->GetVAO());

	//Cycles through each shape, renders their transformation matrices, and draws it to the window.
	for (int i = 0; i < poVecShapes.size(); i++)
	{
		GLint iTranslationMatrixLocation = glGetUniformLocation(uiTexProgram, "matModel");
		glUniformMatrix4fv(iTranslationMatrixLocation, 1, GL_FALSE, glm::value_ptr(*poVecShapes[i]->GetTranslationMatrix()));

		//GLint iTranslationMatrixLocation = glGetUniformLocation(uiProgram, "matTranslation");
		//glUniformMatrix4fv(iTranslationMatrixLocation, 1, GL_FALSE, glm::value_ptr(*poVecShapes[i]->GetTranslationMatrix()));

		//GLint iRotationMatrixLocation = glGetUniformLocation(uiProgram, "matRotation");
		//glUniformMatrix4fv(iRotationMatrixLocation, 1, GL_FALSE, glm::value_ptr(*poVecShapes[i]->GetRotationMatrix()));

		//GLint iScaleMatrixLocation = glGetUniformLocation(uiProgram, "matScale");
		//glUniformMatrix4fv(iScaleMatrixLocation, 1, GL_FALSE, glm::value_ptr(*poVecShapes[i]->GetScaleMatrix()));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(_poWindow);
}