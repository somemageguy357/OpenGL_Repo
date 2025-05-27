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
#include "SceneManager.h"
#include "TextureManager.h"

#include "Camera.h"

#include "CameraBasedMovement.h"

//------GLOBAL VARIABLES------
GLuint uiProgramTex = 0;
GLuint uiProgramReflective = 0;
GLuint uiProgramSkybox = 0;
GLuint uiProgramUI = 0;

CCamera* poCamera = nullptr;

//std::vector<CQuad*> oVecUIElementPtrs;
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

int main()
{
	//Set window size values.
	CWindowManager::SetSize(1280, 720);

	//Attempt to initialize OpenGL setup.
	CWindowManager::SetWindow(InitializeGLSetup());

	//If the setup process succeeded: proceed with the program.
	if (CWindowManager::GetWindow() != nullptr)
	{
		//Enables callback functions for keys, mouse buttons, and mouse position.
		CInputManager::EnableCallbackFunctions();

		//Enable face culling, depth testing, and texture blending.
		CProgramSettings::SetFaceCulling(true);
		CProgramSettings::SetDepthTesting(true);
		CProgramSettings::SetTextureBlending(true);

		//Create programs.
		uiProgramTex = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Lighting_BlinnPhong.frag");
		uiProgramReflective = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Reflection.frag");
		uiProgramSkybox = ShaderLoader::CreateProgram("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag");
		//uiProgramUI = ShaderLoader::CreateProgram("Resources/Shaders/UI.vert", "Resources/Shaders/Texture.frag");
		
		//Create camera.
		poCamera = new CCamera(true, CCamera::ECameraMode::Free, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });

		CSceneManager::CreateSkybox
		(
			{
				"Resources/Textures/Skybox/Right.png",
				"Resources/Textures/Skybox/Left.png",
				"Resources/Textures/Skybox/Top.png",
				"Resources/Textures/Skybox/Bottom.png",
				"Resources/Textures/Skybox/Back.png",
				"Resources/Textures/Skybox/Front.png"
			},
			uiProgramSkybox
		);

		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Prop_Goblin_Tower_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			uiProgramTex,
			{ 0.0f, -5.0f, 0.0f }
		);

		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Wep_Banner_05.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png", "Resources/Textures/ReflectionMap_Banner.png" },
			uiProgramReflective,
			{ 0.0f, -0.25f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 1.5f, 1.5f, 1.5f }
		);

		//poBanner->AddComponentBehaviour(new CCameraBasedMovement(*poBanner->GetTransform()->GetPosition()));

		//CQuad* poButton = new CQuad();
		//oVecUIElementPtrs.push_back(poButton);
		//poButton->AddTexture(oVecTexturePtrs[3]);
	}

	//Main loop.
	while (glfwWindowShouldClose(CWindowManager::GetWindow()) == false)
	{
		Update();
		Render();
	}

	delete poCamera;

	CSceneManager::DestroyScene();
	CTextureManager::DestroyTextures();

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

void Update()
{
	glfwPollEvents();

	CTimeManager::Update();
	CProgramSettings::Update();
	CWindowManager::Update();
	poCamera->Update();
	CSceneManager::Update();

	CInputManager::ClearInputs();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//poCamera->SetProjectionSpace(true, &oVecObjectPtrs);

	CSceneManager::Render();

	//UI rendering.
	//poCamera->SetProjectionSpace(false, &oVecObjectPtrs);

	//for (size_t i = 0; i < oVecUIElementPtrs.size(); i++)
	//{
	//	oVecUIElementPtrs[i]->Render(uiProgramUI);
	//}

	//Swaps the current buffer with the pre-loaded buffer.
	glfwSwapBuffers(CWindowManager::GetWindow());
}