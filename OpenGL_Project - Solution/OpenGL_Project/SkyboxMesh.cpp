#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "SkyboxMesh.h"

#include <iostream>

CSkyboxMesh::CSkyboxMesh(std::string _sFilePath)
{
	MeshSetup();
}

CSkyboxMesh::~CSkyboxMesh() {}

void CSkyboxMesh::MeshSetup()
{
	GenerateVertexData();
	GenerateTriIndices();
	GenerateMesh();
}

void CSkyboxMesh::GenerateVertexData()
{
	//Positions of the skybox's vertices.
	std::vector<float> fVecVertexData =
	{
		//Positions
		//Front
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,	1.0f,  1.0f,

		 //Back
		  1.0f,	 1.0f, -1.0f,
		  1.0f,	-1.0f, -1.0f,
		 -1.0f,	-1.0f, -1.0f,
		 -1.0f,	 1.0f, -1.0f,

		 //Right
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,	1.0f, -1.0f,	

		 //Left
		 -1.0f,	 1.0f, -1.0f,
		 -1.0f,	-1.0f, -1.0f,
		 -1.0f,	-1.0f,  1.0f,
		 -1.0f,	 1.0f,	1.0f,

		 //Top
		 -1.0f,  1.0f, -1.0f,
		 -1.0f,  1.0f,	1.0f,
		  1.0f,  1.0f,	1.0f,
		  1.0f,	 1.0f, -1.0f,

		 //Bottom
		 -1.0f,	-1.0f,	1.0f,
		 -1.0f,	-1.0f, -1.0f,
		  1.0f,	-1.0f, -1.0f,
		  1.0f,	-1.0f,  1.0f,
	};

	m_oVecVertexData.insert(m_oVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

void CSkyboxMesh::GenerateTriIndices()
{
	//Indices of the vertices for the triangles that make up the skybox.
	std::vector<unsigned int> uiVecTriIndices =
	{
		0, 2, 1,
		0, 3, 2,
		4, 6, 5,
		4, 7, 6,
		8, 10, 9,
		8, 11, 10,
		12, 14, 13,
		12, 15, 14,
		16, 18, 17,
		16, 19, 18,
		20, 22, 21,
		20, 23, 22,
	};

	m_oVecTriIndices.insert(m_oVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}

void CSkyboxMesh::GenerateMesh()
{
	//Converting the skybox's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[72];

	for (int i = 0; i < 72; i++)
	{
		fHexVertexData[i] = m_oVecVertexData[i];
	}

	unsigned int uiHexIndices[36];

	for (int i = 0; i < 36; i++)
	{
		uiHexIndices[i] = m_oVecTriIndices[i];
	}

	//Generate the VAO.
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);

	//Generate the EBO.
	GLuint uiEBO = 0;
	glGenBuffers(1, &uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiHexIndices), uiHexIndices, GL_STATIC_DRAW);

	//Generate the VBO.
	GLuint uiVBO = 0;
	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fHexVertexData), fHexVertexData, GL_STATIC_DRAW);

	//Set the Vertex Attribute information (position).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}