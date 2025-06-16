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

#pragma once
#include "TimeManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderLoader.h"
#include "ProgramSettings.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "LightingSettings.h"

#include "Camera.h"

#include "CameraBasedMovement.h"

//------GLOBAL VARIABLES------
ShaderLoader::ShaderProgram* poProgramLit = nullptr;
ShaderLoader::ShaderProgram* poProgramUnlit = nullptr;
ShaderLoader::ShaderProgram* poProgramSkybox = nullptr;
ShaderLoader::ShaderProgram* poProgramUI = nullptr;

CCamera* poCamera = nullptr;
CLightingSettings::SpotLight* poSpotLight = nullptr;
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
		poProgramLit = ShaderLoader::CreateProgram("Resources/Shaders/InstancedArray_Standard.vert", "Resources/Shaders/Lit.frag", ShaderLoader::EShaderType::Lit);
		poProgramUnlit = ShaderLoader::CreateProgram("Resources/Shaders/InstancedArray_Standard.vert", "Resources/Shaders/Unlit.frag", ShaderLoader::EShaderType::Unlit);
		poProgramSkybox = ShaderLoader::CreateProgram("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag", ShaderLoader::EShaderType::Skybox);
		//uiProgramReflective = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert", "Resources/Shaders/Reflection.frag");
		//uiProgramUI = ShaderLoader::CreateProgram("Resources/Shaders/UI.vert", "Resources/Shaders/Texture.frag");
		
		//Create camera.
		poCamera = new CCamera(true, CCamera::ECameraMode::Free, { 0.0f, 3.0f, 10.0f }, { 0.0f, 0.0f, -1.0f });

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
			poProgramSkybox
		);

		#pragma region Models
		//Rune Floor
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Env_Tiles_Rune_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ -8.0f, -0.45f, -8.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 3.0f, 3.0f, 3.0f }
		);

		//Tower
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Prop_Goblin_Tower_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f }
		);

		//Banner
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Wep_Banner_05.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 0.0f, 4.75f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 1.5f, 1.5f, 1.5f }
		);

		//Statue 1
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Env_Statue_02.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 2.0f, -0.25f, 1.0f }
		);

		//Statue 2
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Env_Statue_02.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ -2.0f, -0.25f, 1.0f }
		);

		//Skeleton 1
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Prop_Skeleton_01.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 0.0f, -0.25f, 3.0f },
			{ 0.0f, 38.0f, 0.0f }
		);

		//Skeleton 2
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Prop_Skeleton_01.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 1.7f, -0.25f, 4.5f },
			{ 0.0f, 214.0f, 0.0f }
		);

		//Skeleton 3
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Prop_Skeleton_01.obj",
			{ "Resources/Textures/Dungeons_Texture_01.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ -1.2f, -0.25f, 3.2f },
			{ 0.0f, 104.0f, 0.0f }
		);

		//Weapon 1
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Wep_Crystal_Halberd_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ -0.2f, 0.1f, 3.6f },
			{ 0.0f, 154.0f, 90.0f }
		);

		//Weapon 2
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Wep_Crystal_DoubleSword_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ 0.8f, 0.1f, 2.3f },
			{ 0.0f, 192.0f, 90.0f }
		);

		//Weapon 3
		CSceneManager::CreateModel
		(
			"Resources/Models/SM_Wep_Staff_DoubleBlade_01.obj",
			{ "Resources/Textures/Dungeons_Texture_03.png" },
			poProgramLit,
			{ 1.0f, 1.0f, 1.0f },
			{ -1.8f, -0.1f, 2.8f },
			{ 0.0f, 32.0f, 90.0f }
		);
		#pragma endregion

		glm::vec3 v3fBlueLightPos = { -2.03f, 2.35f, 1.5f };

		//Blue Point Light Model
		CSceneManager::CreateModel
		(
			"Resources/Models/Sphere.obj",
			{ "Resources/Textures/White.png"},
			poProgramUnlit,
			{ 0.0f, 0.0f, 1.0f },
			v3fBlueLightPos,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.15f, 0.15f, 0.15f }
		);

		glm::vec3 v3fRedLightPos = { 1.97f, 2.35f, 1.5f };

		//Red Point Light Model
		CSceneManager::CreateModel
		(
			"Resources/Models/Sphere.obj",
			{ "Resources/Textures/White.png" },
			poProgramUnlit,
			{ 1.0f, 0.0f, 0.0f },
			v3fRedLightPos,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.15f, 0.15f, 0.15f }
		);

		//Light creation.
		CLightingSettings::CreatePointLight(v3fBlueLightPos, { 0.0f, 0.0f, 1.0f }, 0.0f, 1.0f, 0.045f, 0.0075f);
		CLightingSettings::CreatePointLight(v3fRedLightPos, { 1.0f, 0.0f, 0.0f }, 0.0f, 1.0f, 0.045f, 0.0075f);
		CLightingSettings::CreateDirectionalLight({ 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, 0.0f);
		poSpotLight = CLightingSettings::CreateSpotLight(*poCamera->GetTransform()->GetPosition(), *poCamera->GetForwardDirection(), { 1.0f, 1.0f, 1.0f }, 0.0f, 10.0f, 15.0f);
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

	//Enable MSAA.
	glEnable(GL_MULTISAMPLE);
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	//Sets the position and forward direction of the spot light to match the camera's values.
	poSpotLight->v3fPosition = *poCamera->GetTransform()->GetPosition();
	poSpotLight->v3fDirection = *poCamera->GetForwardDirection();

	CSceneManager::Update();

	CInputManager::ClearInputs();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CSceneManager::Render();

	glfwSwapBuffers(CWindowManager::GetWindow());
}