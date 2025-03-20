/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Hexagon.cpp
Description : Contains function definitions for Hexagon.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Hexagon.h"
#include <iostream>

CHexagon::CHexagon() : CShape()
{
	ShapeSetup();
}

CHexagon::CHexagon(TVector3f _v3fPosition) : CShape(_v3fPosition)
{
	ShapeSetup();
}

CHexagon::CHexagon(TVector3f _v3fPosition, TVector3f _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	ShapeSetup();
}

CHexagon::CHexagon(TVector3f _v3fPosition, TVector3f _v3fRotation, TVector3f _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	ShapeSetup();
}

CHexagon::~CHexagon() {}

void CHexagon::ShapeSetup()
{
	SetVertexData();
	SetTriIndices();

	//Converting the hexagon's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[36];

	for (int i = 0; i < 36; i++)
	{
		fHexVertexData[i] = m_fVecVertexData[i];
	}

	unsigned int uiHexIndices[12];

	for (int i = 0; i < 12; i++)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set the Vertex Attribute information (colour).
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void CHexagon::SetVertexData()
{
	//Positions and colours of the hexagon's vertices.
	std::vector<float> fVecVertexData =
	{
		//Positions							//Colours
		0.0f,		0.25f,		0.0f,		1.0f, 1.0f, 1.0f,
		0.215f,		0.125f,		0.0f,		1.0f, 1.0f, 1.0f,
		0.215f,		-0.125f,	0.0f,		1.0f, 1.0f, 1.0f,
		0.0f,		-0.25f,		0.0f,		1.0f, 1.0f, 1.0f,
		-0.215f,	-0.125f,	0.0f,		1.0f, 1.0f, 1.0f,
		-0.215f,	0.125f,		0.0f,		1.0f, 1.0f, 1.0f,
	};

	m_fVecVertexData.insert(m_fVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

void CHexagon::SetTriIndices()
{
	//Indices of the vertices for the triangles that make up the hexagon.
	std::vector<unsigned int> uiVecTriIndices =
	{
		0, 1, 2,
		2, 3, 4,
		4, 5, 0,
		0, 2, 4,
	};

	m_uiVecTriIndices.insert(m_uiVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}