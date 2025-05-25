/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : CubeMesh.cpp
Description : Contains function definitions for CubeMesh.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "CubeMesh.h"

CCubeMesh* CCubeMesh::m_poInstance = nullptr;

CCubeMesh::CCubeMesh()
{
	MeshSetup();
}

CCubeMesh::~CCubeMesh() {}

void CCubeMesh::MeshSetup()
{
	GenerateVertexData();
	GenerateTriIndices();
	GenerateMesh();
}

void CCubeMesh::GenerateVertexData()
{
	//Positions and colours of the cube's vertices.
	std::vector<float> fVecVertexData =
	{
		//Positions							//Colours				//Tex Coords (x, y)
		//Front
		-0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		 0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		 0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,

		//Back
		0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		-0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		-0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,

		//Right
		0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,

		//Left
		-0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		-0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		-0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,

		//Top
		-0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		0.25f,		 0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		0.25f,		 0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,

		//Bottom
		-0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		0.25f,		-0.25f,		-0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		0.25f,		-0.25f,		 0.25f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
	};

	m_oVecVertexData.insert(m_oVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

void CCubeMesh::GenerateTriIndices()
{
	//Indices of the vertices for the triangles that make up the cube.
	std::vector<unsigned int> uiVecTriIndices =
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23,
	};

	m_oVecTriIndices.insert(m_oVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}

void CCubeMesh::GenerateMesh()
{
	//Converting the cube's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[192];

	for (int i = 0; i < 192; i++)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStandard), (void*)(offsetof(VertexStandard, VertexStandard::v3fPosition)));
	glEnableVertexAttribArray(0);

	//Set the Vertex Attribute information (colour).
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStandard), (void*)(offsetof(VertexStandard, VertexStandard::v3fColour)));
	glEnableVertexAttribArray(1);

	//Set the Vertex Attribute information (tex coords).
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStandard), (void*)(offsetof(VertexStandard, VertexStandard::v2fTexCoord)));
	glEnableVertexAttribArray(2);

	//Set the Vertex Attribute information (normals).
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStandard), (void*)(offsetof(VertexStandard, VertexStandard::v3fNormals)));
	glEnableVertexAttribArray(3);
}