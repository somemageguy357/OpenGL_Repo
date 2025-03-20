/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Quad.cpp
Description : Contains function definitions for Quad.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Quad.h"

CQuad::CQuad() : CShape() 
{
	ShapeSetup();
}

CQuad::CQuad(TVector3f _v3fPosition) : CShape(_v3fPosition)
{
	ShapeSetup();
}

CQuad::CQuad(TVector3f _v3fPosition, TVector3f _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	ShapeSetup();
}

CQuad::CQuad(TVector3f _v3fPosition, TVector3f _v3fRotation, TVector3f _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	ShapeSetup();
}

CQuad::~CQuad() {}

void CQuad::ShapeSetup()
{
	SetVertexData();
	SetTriIndices();

	//Converting the quads's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[32];

	for (int i = 0; i < 32; i++)
	{
		fHexVertexData[i] = m_fVecVertexData[i];
	}
	
	unsigned int uiHexIndices[6];

	for (int i = 0; i < 6; i++)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set the Vertex Attribute information (colour).
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Set the Vertex Attribute information (tex coords).
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void CQuad::SetVertexData()
{
	//Positions and colours of the quad's vertices.
	std::vector<float> fVecVertexData =
	{
		//Positions							//Colours				//Tex Coords (x, y)
		-0.25f,		0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		0.25f,		0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		0.25f,		-0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		-0.25f,		-0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	};

	m_fVecVertexData.insert(m_fVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

void CQuad::SetTriIndices()
{
	//Indices of the vertices for the triangles that make up the quad.
	std::vector<unsigned int> uiVecTriIndices =
	{
		0, 1, 2,
		0, 2, 3,
	};

	m_uiVecTriIndices.insert(m_uiVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}