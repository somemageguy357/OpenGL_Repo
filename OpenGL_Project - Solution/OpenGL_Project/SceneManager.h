/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : SceneManager.h
Description : Static class that handles the creation of model objects and the skybox. All objects are updated and rendered via this class.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Model.h"
#include "Skybox.h"

//Static class that handles the creation of model objects and the skybox. All objects are updated and rendered via this class.
class CSceneManager
{
public:
	/// <summary>
	/// Calls Update() on all model objects.
	/// </summary>
	static void Update();

	/// <summary>
	/// Calls Render() on the skybox and all model objects.
	/// </summary>
	static void Render();

	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). The model object's transform values are set to 
	/// their defaults (Position and Rotation: 0.0f, 0.0f, 0.0f | Scale: 1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this object is to use.</param>
	static CModel* CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour);

	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its position. The rotation and 
	/// scale are set to their default values (Rotation: 0.0f, 0.0f, 0.0f | Scale: 1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this object is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	static CModel* CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition);
	
	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its position and rotation. 
	/// The scale is set to its default values (1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this object is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	/// <param name="_v3fRotation:">The rotation of the model object.</param>
	static CModel* CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	
	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its transform values. 
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this object is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	/// <param name="_v3fRotation:">The rotation of the model object.</param>
	/// <param name="_v3fScale:">The scale of the model object.</param>
	static CModel* CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	/// <summary>
	/// Creates a skybox using the given texture file paths.
	/// </summary>
	/// <param name="_oVecTextureFilePaths:">The file paths of the textures.</param>
	/// <param name="_uiProgram:">The rendering program the skybox is to use.</param>
	static void CreateSkybox(std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram);

	/// <summary>
	/// Gets a pointer to the vector containing all model objects.
	/// </summary>
	/// <returns>A pointer to the vector containing all model objects.</returns>
	static std::vector<CModel*>* GetModels();

	/// <summary>
	/// Gets a pointer to the skybox.
	/// </summary>
	/// <returns>A pointer to the skybox.</returns>
	static CSkybox* GetSkybox();

	/// <summary>
	/// Deletes the skybox and all model objects in the scene. Also calls the LightSettings DestroyLights() function.
	/// </summary>
	static void DestroyScene();

private:
	static CSkybox* m_poSkybox;

	static std::vector<CModel*> m_oVecModelPtrs;

	CSceneManager() = delete;
	~CSceneManager() = delete;
};