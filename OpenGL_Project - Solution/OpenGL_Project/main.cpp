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

#include "TimeManager.h"
#include "WindowManager.h"
#include "ShaderLoader.h"

#include "Camera.h"
#include "Texture.h"
#include "Hexagon.h"
#include "Quad.h"
#include "Cube.h"

//------GLOBAL VARIABLES------
GLuint uiProgramTex = 0;
GLuint uiProgramTexMix = 0;

CCamera* poCamera = nullptr;
std::vector<CTexture*> oVecTexturePtrs;
std::vector<CShape*> oVecShapePtrs;
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

/// <summary>
/// Creates an animated CTexture which gets its texture data from the given file path.
/// </summary>
/// <param name="_sFilePath:">The file path of the image file.</param>
/// <param name="_iFrames:">The total number of frames in the spritesheet.</param>
/// <param name="_iRows:">The number of rows in the spritesheet.</param>
/// <param name="_iColumns:">The number of columns in the spritesheet.</param>
/// <param name="_iFrameRate:">The frame rate of the texture's animation.</param>
void CreateTexture(std::string _sFilePath, int _iFrames, int _iRows, int _iColumns, int _iFrameRate);

int main()
{
	//Set window size values.
	CWindowManager::SetSize(800, 800);

	//Attempt to initialize OpenGL setup.
	GLFWwindow* poWindow = InitializeGLSetup();

	bool bCloseProgram = false;

	//If the setup process failed: prepare to close/terminate the program
	if (poWindow == nullptr)
	{
		bCloseProgram = true;
	}

	//Else: proceed with the program.
	else
	{
		//Create camera.
		poCamera = new CCamera(true, { 0.0f, 0.0f, 3.0f });

		//Enable texture blending.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Enable depth testing.
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//Enable face culling.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		//Enable wireframe.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Create programs.
		uiProgramTex = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Texture.frag");
		//uiProgramTexMix = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/TextureMix.frag");

		//Create textures.
		CreateTexture("Resources/Textures/testtex.png");

		//Create cube.
		for (int i = 0; i < 1; i++)
		{
			CCube* poCube = new CCube();
			oVecShapePtrs.push_back(poCube);

			//Increase the scale of the quad if the camera is using orthographic projection.
			if (poCamera->GetProjectionSpace() == false)
			{
				poCube->GetTransform()->SetScaleMultiplier(400.0f);
			}
		}

		oVecShapePtrs[0]->GetTransform()->SetScale(2.0f);
		oVecShapePtrs[0]->AddTexture(oVecTexturePtrs[0]);
	}

	//Main loop.
	while (bCloseProgram == false && glfwWindowShouldClose(poWindow) == false)
	{
		Update();
		Render(poWindow);
	}

	//Clean up the program. Delete pointers and terminate the render window.
	for (int i = 0; i < oVecShapePtrs.size(); i++)
	{
		delete oVecShapePtrs[i];
	}

	oVecShapePtrs.clear();

	for (int i = 0; i < oVecTexturePtrs.size(); i++)
	{
		delete oVecTexturePtrs[i];
	}

	oVecTexturePtrs.clear();

	delete poCamera;

	glfwTerminate();
}

GLFWwindow* InitializeGLSetup()
{
	//Title of the window.
	std::string sWindowTitle = "Main Window (" + std::to_string(CWindowManager::GetWidth()) + "x" + std::to_string(CWindowManager::GetHeight()) + ")";

	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* poWindow = glfwCreateWindow(CWindowManager::GetWidth(), CWindowManager::GetHeight(), sWindowTitle.c_str(), NULL, NULL);

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
	glViewport(0, 0, CWindowManager::GetWidth(), CWindowManager::GetHeight());

	return poWindow;
}

void CreateTexture(std::string _sFilePath)
{
	CTexture* poTexture = new CTexture(_sFilePath);
	oVecTexturePtrs.push_back(poTexture);
}

void CreateTexture(std::string _sFilePath, int _iFrames, int _iRows, int _iColumns, int _iFrameRate)
{
	CTexture* poTexture = new CTexture(_sFilePath, _iFrames, _iRows, _iColumns, _iFrameRate);
	oVecTexturePtrs.push_back(poTexture);
}

void Update()
{
	glfwPollEvents();

	CTimeManager::SetDeltaTime((float)glfwGetTime() - CTimeManager::GetCurrentTime());
	CTimeManager::SetCurrentTime((float)glfwGetTime());

	oVecShapePtrs[0]->GetTransform()->AddRotation(CTimeManager::GetDeltaTime() * 45.0f, { 0.0f, 1.0f, 0.0f });
	//poCamera->GetTransform()->SetPosition({ sin(CTimeManager::GetCurrentTime()) * 2.0f, poCamera->GetTransform()->GetPosition()->y, poCamera->GetTransform()->GetPosition()->z });
	poCamera->Update();
}

void Render(GLFWwindow* _poWindow)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	poCamera->Render(uiProgramTex, oVecShapePtrs[0]);

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(_poWindow);
}