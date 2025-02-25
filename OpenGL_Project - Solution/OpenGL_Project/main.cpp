#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <string>
#include "ShaderLoader.h"

//------GLOBAL VARIABLES------
const int kiWindowWidth = 800;
const int kiWindowHeight = 800;

GLuint uiProgramFixedTri = 0;

GLfloat fTriVertices[] = 
{
	0.0f, 0.0f, 0.0f,
	-0.5f, 0.8f, 0.0f,
	0.5f, 0.8f, 0.0f,
};

GLuint uiProgramPositionOnly;
GLuint uiVBOTri;
GLuint uiVAOTri;
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
	//asdasd
	uiProgramFixedTri = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
	uiProgramPositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/PositionOnly.vert", "Resources/Shaders/FixedColor.frag");

	//---------------------------
	//Generate the VAO for a triangle.
	//---------------------------
	//(n: number of vertex array objects to be generated, arrays: the array the objects are stored in)
	glGenVertexArrays(1, &uiVAOTri);

	//(array: the VAO to bind)
	glBindVertexArray(uiVAOTri);

	//---------------------------
	//Generate VBO for a triangle.
	//---------------------------
	//(n: number of buffer objects to be generated, buffers: the array the objects are stored in)
	glGenBuffers(1, &uiVBOTri);

	//(target: bound target for buffer, buffer: buffer to bind)
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOTri); //vertex buffer object
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBOTri); //element buffer object

	//(target: bound target for buffer, size: byte size of the object, data: pointer to data that is to be copied into buffer, usage: expected usage pattern)
	glBufferData(GL_ARRAY_BUFFER, sizeof(fTriVertices), fTriVertices, GL_STATIC_DRAW); //Created and modified once and used many times.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(fTriVertices), fTriVertices, GL_DYNAMIC_DRAW); //Modified and repeatedly used many times.

	//----------------------------------------------------------
	//Set the Vertex Attribute information (how to interpret the vertex data).
	//----------------------------------------------------------
	//index: 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

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
}

void Render(GLFWwindow* _poWindow)
{
	//Indicates the buffers to be cleared.
	glClear(GL_COLOR_BUFFER_BIT); //Buffers currently enabled for color writing.
	//glClear(GL_DEPTH_BUFFER_BIT); //The depth buffer.

	glUseProgram(uiProgramFixedTri);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(_poWindow); //The window whose buffers are to be swapped.
}