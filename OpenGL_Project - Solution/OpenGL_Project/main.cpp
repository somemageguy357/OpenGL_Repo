#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include "ShaderLoader.h"

//------GLOBAL VARIABLES------
const int kiWindowWidth = 800;
const int kiWindowHeight = 800;

float fCurrentTime = 0.0f;

GLuint uiProgramColourFade = 0;

GLfloat fQuad1[] = 
{
	//Position				//Colour
	-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	0.5f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,
};

GLfloat fQuad2[] =
{
	//Position				//Colour
	-0.25f, 0.25f, 0.0f,	1.0f, 1.0f, 1.0f,
	0.25f, 0.25f, 0.0f,		0.0f, 0.0f, 1.0f,
	0.25f, -0.25f, 0.0f,	0.0f, 1.0f, 0.0f,
	-0.25f, -0.25f, 0.0f,	1.0f, 0.0f, 0.0f,
};

GLuint iQuad2Indices[] =
{
	0, 1, 2,
	0, 2, 3,
};

GLuint uiVBOQuad1 = 0;
GLuint uiVAOQuad1 = 0;

GLuint uiVBOQuad2 = 0;
GLuint uiVAOQuad2 = 0;

GLuint uiEBOQuad2 = 0;

glm::vec3 QuadPosition = glm::vec3(0.5f, 0.5f, 0.0f);
glm::mat4 TranslationMatrix;

float QuadRotation = 45.0f;
glm::mat4 RotationMatrix;

glm::vec3 QuadScale = glm::vec3(0.5f, 0.5f, 1.0f);
glm::mat4 ScaleMatrix;
//----------------------------

GLFWwindow* InitializeGLSetup();
void Update(GLFWwindow* _poWindow);
void Render(GLFWwindow* _poWindow);

int main()
{
	bool bCloseProgram = false;
	GLFWwindow* poWindow = InitializeGLSetup();

	if (poWindow == nullptr)
	{
		bCloseProgram = true;
	}

	uiProgramColourFade = ShaderLoader::CreateProgram("Resources/Shaders/WorldSpace.vert", "Resources/Shaders/VertexColourFade.frag");

	#pragma region Quad1
	//Generate the VAO.
	//glGenVertexArrays(1, &uiVAOQuad1);
	//glBindVertexArray(uiVAOQuad1);

	////Generate the VBO.
	//glGenBuffers(1, &uiVBOQuad1);
	//glBindBuffer(GL_ARRAY_BUFFER, uiVBOQuad1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(fQuad1), fQuad1, GL_STATIC_DRAW);

	////Set the Vertex Attribute information (colour).
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	#pragma endregion

	#pragma region Quad2
	//Generate the VAO.
	glGenVertexArrays(1, &uiVAOQuad2);
	glBindVertexArray(uiVAOQuad2);

	//Generate the EBO.
	glGenBuffers(1, &uiEBOQuad2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBOQuad2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iQuad2Indices), iQuad2Indices, GL_STATIC_DRAW);

	//Generate the VBO.
	glGenBuffers(1, &uiVBOQuad2);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOQuad2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fQuad2), fQuad2, GL_STATIC_DRAW);

	//Set the Vertex Attribute information.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set the Vertex Attribute information (colour).
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	#pragma endregion

	//Main loop.
	while (bCloseProgram == false && glfwWindowShouldClose(poWindow) == false)
	{
		Update(poWindow);
		Render(poWindow);
	}

	glfwTerminate();
}

GLFWwindow* InitializeGLSetup()
{
	//Title of the window.
	std::string sWindowTitle = "Main Window (" + std::to_string(kiWindowWidth) + "x" + std::to_string(kiWindowHeight) + ")";

	//GLFW inits.
	glfwInit(); //Initializes the GLFW library. Required before other GLFW functions can be used.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //Indicates the OpenGL profile used by the context.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //API version number that the context must be compatible with. "4.x".
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); //API version number that the context must be compatible with. "x.6".

	//Second to last NULL determines the monitor to display on. NULL for windowed mode.
	GLFWwindow* poWindow = glfwCreateWindow(kiWindowWidth, kiWindowHeight, sWindowTitle.c_str(), NULL, NULL);

	//If the window fails to create: terminate it.
	if (poWindow == nullptr)
	{
		std::cout << "GLFW failed. Ending program..." << std::endl;
		system("pause");
		glfwTerminate(); //glfwInit() must be called again to use GLFW functions after this is called.
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

void Update(GLFWwindow* _poWindow)
{
	glfwPollEvents();

	TranslationMatrix = glm::translate(glm::mat4(1.0f), QuadPosition);
	RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(QuadRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	ScaleMatrix = glm::scale(glm::mat4(1.0f), QuadScale);

	fCurrentTime = (float)glfwGetTime();
}

void Render(GLFWwindow* _poWindow)
{
	//Indicates the buffers to be cleared.
	glClear(GL_COLOR_BUFFER_BIT); //Buffers currently enabled for color writing.

	glUseProgram(uiProgramColourFade);

	GLint iCurrentTimeLocation = glGetUniformLocation(uiProgramColourFade, "fCurrentTime");
	glUniform1f(iCurrentTimeLocation, fCurrentTime);

	GLint TranslationMatrixLocation = glGetUniformLocation(uiProgramColourFade, "TranslationMatrix");
	glUniformMatrix4fv(TranslationMatrixLocation, 1, GL_FALSE, glm::value_ptr(TranslationMatrix));

	GLint RotationMatrixLocation = glGetUniformLocation(uiProgramColourFade, "RotationMatrix");
	glUniformMatrix4fv(RotationMatrixLocation, 1, GL_FALSE, glm::value_ptr(RotationMatrix));

	GLint ScaleMatrixLocation = glGetUniformLocation(uiProgramColourFade, "ScaleMatrix");
	glUniformMatrix4fv(ScaleMatrixLocation, 1, GL_FALSE, glm::value_ptr(ScaleMatrix));

	//Two Tris
	//glBindVertexArray(uiVAOQuad1);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	//glBindVertexArray(uiVAOQuad2);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	//Quad
	glBindVertexArray(uiVAOQuad2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(_poWindow); //The window whose buffers are to be swapped.
}