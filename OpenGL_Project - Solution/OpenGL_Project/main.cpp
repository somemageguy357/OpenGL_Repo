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

#include "ShaderLoader.h"
#include "Camera.h"
#include "Texture.h"
#include "Hexagon.h"
#include "Quad.h"

//------GLOBAL VARIABLES------
const int kiWindowWidth = 800;
const int kiWindowHeight = 800;

float fCurrentTime = 0.0f;
float fDeltaTime = 0.0f;

GLuint uiProgramTex = 0;
GLuint uiProgramTexMix = 0;

CCamera* poCamera = nullptr;
std::vector<CTexture*> poVecTextures;
std::vector<CShape*> poVecShapes;
//----------------------------

/// <summary>
/// Sets up the OpenGL framework and attempts to create the window that the program renders to.
/// </summary>
/// <returns>The window the program renders to, nullptr if the process fails.</returns>
GLFWwindow* InitializeGLSetup();

/// <summary>
/// Updates any transform changes made to any chosen objects.
/// </summary>
void Update();

/// <summary>
/// Renders all objects to the window and swaps the buffers.
/// </summary>
/// <param name="_poWindow:">The window that buffers are swapped to.</param>
void Render(GLFWwindow* _poWindow);

/// <summary>
/// Creates a CTexture which gets its texture data from the given file path.
/// </summary>
/// <param name="_sFilePath:">The file path of the image file.</param>
void CreateTexture(std::string _sFilePath);

int main()
{
	bool bCloseProgram = false;
	GLFWwindow* poWindow = InitializeGLSetup();

	//If the setup process failed: prepare to close/terminate the program
	if (poWindow == nullptr)
	{
		bCloseProgram = true;
	}

	//Else: proceed with the program.
	else
	{
		//Create camera.
		poCamera = new CCamera(kiWindowWidth, kiWindowHeight, { 0.0f, 0.0f, 3.0f });

		//Enable texture blending.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Create programs.
		uiProgramTex = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Texture.frag");
		uiProgramTexMix = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/TextureMix.frag");

		//Create textures.
		CreateTexture("Resources/Textures/Run.png");
		CreateTexture("Resources/Textures/Run (3).png");

		//Create quads.
		for (int i = 0; i < 4; i++)
		{
			CQuad* poQuad = new CQuad();
			poVecShapes.push_back(poQuad);
			poQuad->SetScale({ 500.0f, 500.0f, 1.0f });
		}

		//Reposition quads, add textures to them, and change tex coords for some.
		poVecShapes[0]->SetPosition({ -200.0f, 200.0f, 0.0f });
		poVecShapes[1]->SetPosition({ 200.0f, 200.0f, 0.0f });
		poVecShapes[2]->SetPosition({ 200.0f, -200.0f, 0.0f });
		poVecShapes[3]->SetPosition({ -200.0f, -200.0f, 0.0f });

		poVecShapes[0]->AddTexture(poVecTextures[0]);
		poVecShapes[1]->AddTexture(poVecTextures[0]);
		poVecShapes[1]->AddTexture(poVecTextures[1]); //Second texture for mixing
		poVecShapes[2]->AddTexture(poVecTextures[0]);
		poVecShapes[3]->AddTexture(poVecTextures[0]);

		poVecShapes[0]->SetNewQuadTexCoords({ -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f }); //Tiling
		poVecShapes[2]->SetNewQuadTexCoords({ 0.0f, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f }); //Vertical Flip
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

	delete poCamera;

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

void CreateTexture(std::string _sFilePath)
{
	CTexture* poTexture = new CTexture(_sFilePath);
	poVecTextures.push_back(poTexture);
}

void Update()
{
	glfwPollEvents();

	fDeltaTime = (float)glfwGetTime() - fCurrentTime;
	fCurrentTime = (float)glfwGetTime();

	poCamera->SetPosition({ sin(fCurrentTime) * 90.0f, poCamera->GetPosition()->y, poCamera->GetPosition()->z });
	poCamera->Update();
}

void Render(GLFWwindow* _poWindow)
{
	glClear(GL_COLOR_BUFFER_BIT);

	poCamera->Render(uiProgramTex, poVecShapes[0], fCurrentTime); //Tiling
	poCamera->Render(uiProgramTexMix, poVecShapes[1], fCurrentTime); //Mixing
	poCamera->Render(uiProgramTex, poVecShapes[2], fCurrentTime); //Flip
	poCamera->Render(uiProgramTex, poVecShapes[3], fCurrentTime); //Blend

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(_poWindow);
}