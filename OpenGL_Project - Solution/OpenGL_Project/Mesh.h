/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Mesh.h
Description : Base class for all mesh types. Contains a mesh's vertex data.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

class CMesh
{
public:
	struct VertexStandard
	{
		glm::vec3 v3fPosition;
		glm::vec3 v3fColour;
		glm::vec2 v2fTexCoord;
		glm::vec3 v3fNormals;

		VertexStandard()
		{
			v3fPosition = { 0.0f, 0.0f, 0.0f };
			v3fColour = { 0.0f, 0.0f, 0.0f };
			v2fTexCoord = { 0.0f, 0.0f };
			v3fNormals = { 0.0f, 0.0f, 0.0f };
		}

		VertexStandard(glm::vec3 _v3fPosition, glm::vec3 _v3fColour, glm::vec2 _v2fTexCoord, glm::vec3 _v3fNormals)
		{
			v3fPosition = _v3fPosition;
			v3fColour = _v3fColour;
			v2fTexCoord = _v2fTexCoord;
			v3fNormals = _v3fNormals;
		}
	};

	~CMesh();

	/// <summary>
	/// Returns the address of the Object's VAO.
	/// </summary>
	/// <returns>The Object's VAO.</returns>
	GLuint* GetVAO();

	/// <summary>
	/// Returns the vector of floats containing vertex position and colour data.
	/// </summary>
	/// <returns>The vector of floats containing vertex position and colour data.</returns>
	std::vector<float>* GetVertexData();

	/// <summary>
	/// Returns the vector of uints containing the vertex joints of the tris that make up the Object.
	/// </summary>
	/// <returns>The vector of uints containing the vertex joints of the tris that make up the Object.</returns>
	std::vector<unsigned int>* GetTriIndices();

protected:
	GLuint m_uiVAO = 0;

	//Positions, colours, and texture coordinates of the mesh's vertices.
	std::vector<float> m_oVecVertexData;

	//Indices of the vertices for the triangles that make up the mesh.
	std::vector<unsigned int> m_oVecTriIndices;

	CMesh();

	//Wraps the generative functions of the mesh. Called from the mesh's constructors.
	virtual void MeshSetup() {};

	//Generates the default vertex data of the particular mesh.
	virtual void GenerateVertexData() {};

	//Generates the default tri indice data of the particular mesh.
	virtual void GenerateTriIndices() {};

	//Generates the mesh's render data (buffers, vertex pointers, etc).
	virtual void GenerateMesh() {};
};