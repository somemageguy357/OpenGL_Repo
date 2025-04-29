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

	/// <summary>
	/// Returns the address of the shape's VAO.
	/// </summary>
	/// <returns>The shape's VAO.</returns>
	GLuint* GetVAO();

	/// <summary>
	/// Returns the vector of floats containing vertex position and colour data.
	/// </summary>
	/// <returns>The vector of floats containing vertex position and colour data.</returns>
	std::vector<float> GetVertexData();

	/// <summary>
	/// Returns the vector of uints containing the vertex joints of the tris that make up the shape.
	/// </summary>
	/// <returns>The vector of uints containing the vertex joints of the tris that make up the shape.</returns>
	std::vector<unsigned int> GetTriIndices();

protected:
	GLuint m_uiVAO = 0;

	//Positions, colours, and texture coordinates of the mesh's vertices.
	std::vector<float> m_oVecVertexData;

	//Indices of the vertices for the triangles that make up the mesh.
	std::vector<unsigned int> m_oVecTriIndices;

	CMesh();
	~CMesh();

	//Wraps the generative functions of the mesh. Called from the mesh's constructors.
	virtual void MeshSetup() = 0;

	//Generates the default vertex data of the particular mesh.
	virtual void GenerateVertexData() = 0;

	//Generates the default tri indice data of the particular mesh.
	virtual void GenerateTriIndices() = 0;

	//Generates the mesh's render data (buffers, vertex pointers, etc).
	virtual void GenerateMesh() = 0;
};