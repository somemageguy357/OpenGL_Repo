/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Skybox.h
Description : An object representing a skybox.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Camera.h"
#include "SkyboxMesh.h"
#include "ShaderLoader.h"

class CSkybox
{
public:
	CSkybox() = delete;

	/// <summary>
	/// Creates a skybox using the given texture file paths.
	/// </summary>
	/// <param name="_uiProgram:">The rendering program for the skybox.</param>
	/// <param name="_oVecImageFilePaths:">The file paths of the textures.</param>
	CSkybox(ShaderLoader::ShaderProgram* _poProgram, std::vector<std::string> _oVecImageFilePaths);

	~CSkybox();

	/// <summary>
	/// Renders the skybox.
	/// </summary>
	/// <param name="_poCamera:">The main camera.</param>
	void Render(CCamera* _poCamera);

	/// <summary>
	/// Returns the texture ID of the cubemap.
	/// </summary>
	/// <returns>The texture ID of the cubemap.</returns>
	GLuint* GetTextureID();

private:
	CMesh* m_poMesh = nullptr;

	ShaderLoader::ShaderProgram* m_poProgram = nullptr;
	GLuint m_uiTextureID = 0;

	void CreateTextures(std::vector<std::string> _oVecImageFilePaths);
};