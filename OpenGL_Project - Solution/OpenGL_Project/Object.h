/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Object.h
Description : Base class for all Object types. Contains vertex, rendering object, and texture data for the Object as well as its transform.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "ComponentBehaviour.h"
#include "TextureManager.h"
#include "ShaderLoader.h"

#include "Skybox.h"
#include "Camera.h"

#include <vector>

/// <summary>
/// Base class for all 2D and 3D objects. Contains an object's vertex data, rendering object data, and textures
/// as well as its transform. Objects of this type specifically cannot be created.
/// </summary>
class CObject
{
public:
	struct VertexStandard
	{
		glm::vec3 v3fPosition;
		glm::vec3 v3fColour;
		glm::vec2 v2fTexCoord;

		VertexStandard()
		{
			v3fPosition = { 0.0f, 0.0f, 0.0f };
			v3fColour = { 0.0f, 0.0f, 0.0f };
			v2fTexCoord = { 0.0f, 0.0f };
		}

		VertexStandard(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, glm::vec2 _v2fTexCoord)
		{
			v3fPosition = _v3fPosition;
			v3fColour = _v3fColour;
			v2fTexCoord = _v2fTexCoord;
		}
	};

	~CObject();

	void Update();

	virtual void Render(CSkybox* _poSkybox, CCamera* _poCamera) = 0;

	/// <summary>
	/// Returns the Object's transform.
	/// </summary>
	/// <returns>The Object's transform.</returns>
	CTransform* GetTransform();

	CMesh* GetMesh();

	void AddTexture(std::string _sTextureFilePath);

	std::vector<GLuint> GetTextureIDs();

	/// <summary>
	/// Binds all of the Object's textures to be used for rendering. Should only be done during the rendering stage of the program.
	/// </summary>
	/// <param name="_uiProgram:">The program that the textures are to use.</param>
	void BindTextures(GLuint _uiProgram);

	void AddComponentBehaviour(CComponentBehaviour* _poComponentBehaviour);

protected:
	//The Object's transform.
	CTransform m_oTransform;

	CMesh* m_poMesh = nullptr;

	ShaderLoader::ShaderProgram* m_poProgram = nullptr;

	//The vector containing the Object's TextureIDs.
	std::vector<GLuint> m_oVecTextureIDs;

	std::vector<CComponentBehaviour*> m_oVecComponentBehaviourPtrs;

	/// <summary>
	/// Creates a Object with default transform data. Position: (0.0f, 0.0f, 0.0f). Rotation: (0.0f, 0.0f, 0.0f). Scale: (1.0f, 1.0f, 1.0f).
	/// </summary>
	CObject();

	/// <summary>
	/// Creates a Object with the given position value. Sets rotation (0.0f, 0.0f, 0.0f) and scale (1.0f, 1.0f, 1.0f) to their 
	/// default values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the Object.</param>
	CObject(glm::vec3 _v3fPosition);

	/// <summary>
	/// Creates a Object with the given position and rotation values. Sets scale (1.0f, 1.0f, 1.0f) to its default value.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the Object.</param>
	/// <param name="_v3fRotation:">The starting rotation of the Object.</param>
	CObject(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation);

	/// <summary>
	/// Creates a Object with the given transform values.
	/// </summary>
	/// <param name="_v3fPosition:">The starting position of the Object.</param>
	/// <param name="_v3fRotation:">The starting rotation of the Object.</param>
	/// <param name="_v3fScale:">The starting scale of the Object.</param>
	CObject(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

};