/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Cube.cpp
Description : Contains function definitions for Cube.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Cube.h"

CCube::CCube() : CShape()
{
	ShapeSetup();
}

CCube::CCube(glm::vec3 _v3fPosition) : CShape(_v3fPosition)
{
	ShapeSetup();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	ShapeSetup();
}

CCube::CCube(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	ShapeSetup();
}

CCube::~CCube() {}

void CCube::ShapeSetup()
{
	GenerateVertexData();
	GenerateTriIndices();
	GenerateShape();
}

void CCube::GenerateVertexData()
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

	m_fVecVertexData.insert(m_fVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

void CCube::GenerateTriIndices()
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

	m_uiVecTriIndices.insert(m_uiVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}

void CCube::GenerateShape()
{
	//Converting the cube's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[192];

	for (int i = 0; i < 192; i++)
	{
		fHexVertexData[i] = m_fVecVertexData[i];
	}

	unsigned int uiHexIndices[36];

	for (int i = 0; i < 36; i++)
	{
		uiHexIndices[i] = m_uiVecTriIndices[i];
	}

	//Generate the VAO.
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);

	//Generate the EBO.
	glGenBuffers(1, &m_uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiHexIndices), uiHexIndices, GL_STATIC_DRAW);

	//Generate the VBO.
	glGenBuffers(1, &m_uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
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
}