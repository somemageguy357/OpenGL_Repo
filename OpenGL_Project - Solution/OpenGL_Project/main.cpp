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
#include "InputManager.h"
#include "ShaderLoader.h"
#include "ProgramSettings.h"

#include "Camera.h"
#include "Skybox.h"
#include "Texture.h"
#include "Hexagon.h"
#include "Quad.h"
#include "Cube.h"
#include "Model.h"

#include "CameraBasedMovement.h"

//------GLOBAL VARIABLES------
GLuint uiProgramTex = 0;
GLuint uiProgramSkybox = 0;

CCamera* poCamera = nullptr;
CSkybox* poSkybox = nullptr;

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
void Render();

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
	CWindowManager::SetWindow(InitializeGLSetup());

	//If the setup process succeeded: proceed with the program.
	if (CWindowManager::GetWindow() != nullptr)
	{
		//Create camera.
		poCamera = new CCamera(true, { 0.0f, 0.0f, 3.0f });
		poCamera->SetCameraMode(CCamera::ECameraMode::Orbital);

		//Enables callback functions for keys, mouse buttons, and mouse position.
		CInputManager::EnableCallbackFunctions();

		//Enable face culling, depth testing, and texture blending.
		CProgramSettings::SetFaceCulling(true);
		CProgramSettings::SetDepthTesting(true);
		CProgramSettings::SetTextureBlending(true);

		//Create programs.
		uiProgramTex = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Reflection.frag");
		uiProgramSkybox = ShaderLoader::CreateProgram("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag");

		poSkybox = new CSkybox
		(uiProgramSkybox,
			{
				"Resources/Textures/Skybox/Right.png",
				"Resources/Textures/Skybox/Left.png",
				"Resources/Textures/Skybox/Top.png",
				"Resources/Textures/Skybox/Bottom.png",
				"Resources/Textures/Skybox/Back.png",
				"Resources/Textures/Skybox/Front.png"
			}
		);

		//Create textures.
		CreateTexture("Resources/Textures/Dungeons_Texture_01.png");
		CreateTexture("Resources/Textures/Dungeons_Texture_03.png");

		//Create cube.
		//for (int i = 0; i < 3; i++)
		//{
		//	CCube* poCube = new CCube();
		//	oVecShapePtrs.push_back(poCube);

		//	//Increase the scale of the quad if the camera is using orthographic projection.
		//	if (poCamera->GetProjectionSpace() == false)
		//	{
		//		poCube->GetTransform()->SetScaleMultiplier(400.0f);
		//	}

		//	poCube->AddTexture(oVecTexturePtrs[0]);
		//}

		CModel* poTower = new CModel("Resources/Models/SM_Prop_Goblin_Tower_01.obj", poSkybox);
		oVecShapePtrs.push_back(poTower);
		poTower->AddTexture(oVecTexturePtrs[1]);

		CModel* poBanner = new CModel("Resources/Models/SM_Wep_Banner_05.obj", poSkybox);
		oVecShapePtrs.push_back(poBanner);
		poBanner->AddTexture(oVecTexturePtrs[0]);

		poBanner->AddComponentBehaviour(new CCameraBasedMovement());

		oVecShapePtrs[0]->GetTransform()->SetPosition({ 0.0f, -5.0f, 0.0f });
		oVecShapePtrs[1]->GetTransform()->SetScale(1.5f);
		oVecShapePtrs[1]->GetTransform()->SetPosition({ 0.0f, -0.0f, 0.0f });
	}

	//Main loop.
	while (glfwWindowShouldClose(CWindowManager::GetWindow()) == false)
	{
		Update();
		Render();
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

	CProgramSettings::Update();
	CWindowManager::Update();
	poCamera->Update();

	for (size_t i = 0; i < oVecShapePtrs.size(); i++)
	{
		oVecShapePtrs[i]->Update();
	}

	CInputManager::ClearInputs();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < oVecShapePtrs.size(); i++)
	{
		oVecShapePtrs[i]->Render(uiProgramTex);
	}

	poSkybox->Render();

	//UI rendering?
	//poCamera->SetProjectionSpace(false, &oVecShapePtrs);

	//for (size_t i = 0; i < oVecUIElements.size(); i++)
	//{
	//	poCamera->Render(uiProgramTex, oVecUIElements[i]);
	//}

	//poCamera->SetProjectionSpace(true, &oVecShapePtrs);

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(CWindowManager::GetWindow());
}