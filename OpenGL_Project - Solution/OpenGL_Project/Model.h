/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Model.h
Description : An object representing a model created through an obj loader.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Object.h"
#include "Skybox.h"

class CModel : public CObject
{
public:
	CModel() = delete;

	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). The model object's transform values are set to 
	/// their defaults (Position and Rotation: 0.0f, 0.0f, 0.0f | Scale: 1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this model is to use.</param>
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour);

	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its position. The rotation and 
	/// scale are set to their default values (Rotation: 0.0f, 0.0f, 0.0f | Scale: 1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this model is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition);
	
	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its position and rotation. 
	/// The scale is set to its default values (1.0f, 1.0f, 1.0f).
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this model is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	/// <param name="_v3fRotation:">The rotation of the model object.</param>
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);
	
	/// <summary>
	/// Creates a model object using the given file paths for both its vertex data and texture(s). Also sets its transform values. 
	/// </summary>
	/// <param name="_sModelFilePath:">The file path of the model.</param>
	/// <param name="_oVecTextureFilePaths:">The file path(s) of the texture(s).</param>
	/// <param name="_uiProgram:">The rendering program this object is to use.</param>
	/// <param name="_v3fPosition:">The position of the model object.</param>
	/// <param name="_v3fRotation:">The rotation of the model object.</param>
	/// <param name="_v3fScale:">The scale of the model object.</param>
	CModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);
	
	~CModel();

	/// <summary>
	/// Renders the model.
	/// </summary>
	/// <param name="_poSkybox:">The skybox, for reflective textures.</param>
	/// <param name="_poCamera:">The main camera.</param>
	void Render(CSkybox* _poSkybox, CCamera* _poCamera) override;

private:
	void ModelSetup(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, ShaderLoader::ShaderProgram* _poProgram, glm::vec3 _v3fColour);

	/// <summary>
	/// Renders the model, using its MVP matrix and the current camera position.
	/// </summary>
	/// <param name="_poCamera:">The main camera.</param>
	void RenderModel(CCamera* _poCamera);

	/// <summary>
	/// Renders all lighting values on the model.
	/// </summary>
	void RenderLighting();

	/// <summary>
	/// Renders the reflection of the model. Uses the skybox for its reflections.
	/// </summary>
	/// <param name="_poSkybox:">The skybox that is reflected.</param>
	void RenderReflections(CSkybox* _poSkybox);

};