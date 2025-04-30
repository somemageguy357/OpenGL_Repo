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
#include <iostream>

CQuad::CQuad() : CShape() 
{
	//ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition) : CShape(_v3fPosition)
{
	//ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CShape(_v3fPosition, _v3fRotation)
{
	//ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CShape(_v3fPosition, _v3fRotation, _v3fScale)
{
	//ShapeSetup();
}

CQuad::~CQuad() {}

void CQuad::Render(GLuint _uiProgram)
{
}

//void CQuad::ShapeSetup()
//{
//	GenerateVertexData();
//	GenerateTriIndices();
//	GenerateShape();
//}
//
//void CQuad::GenerateVertexData()
//{
//	//Positions and colours of the quad's vertices.
//	std::vector<float> fVecVertexData =
//	{
//		//Positions							//Colours				//Tex Coords (x, y)
//		-0.25f,		0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
//		0.25f,		0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
//		0.25f,		-0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
//		-0.25f,		-0.25f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
//	};
//
//	m_fVecVertexData.insert(m_fVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
//}
//
void CQuad::SetNewQuadTexCoords(std::vector<float> _fVecNewTexCoords)
{
	////Requires 8 elements as there are 8 texture coordinate values.
	//if (_fVecNewTexCoords.size() != 8)
	//{
	//	std::cout << "Attempt to set new texture coordinates for a quad failed: incorrect number of elements supplied in vector (expecting 8)." << std::endl;
	//	return;
	//}

	////Index positions of the tex coords: 6,7	14,15	22,23	30,31
	//for (size_t iRows = 0; iRows < 4; iRows++)
	//{
	//	m_fVecVertexData[6 + (iRows * 8)] = _fVecNewTexCoords[iRows * 2];
	//	m_fVecVertexData[7 + (iRows * 8)] = _fVecNewTexCoords[(iRows * 2) + 1];
	//}

	////Regenerate the shape with the updated vertex data.
	//GenerateShape();
}
//
//void CQuad::GenerateTriIndices()
//{
//	//Indices of the vertices for the triangles that make up the quad.
//	std::vector<unsigned int> uiVecTriIndices =
//	{
//		0, 1, 2,
//		0, 2, 3,
//	};
//
//	m_uiVecTriIndices.insert(m_uiVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
//}
//
//void CQuad::GenerateShape()
//{
//	//Converting the quads's vertex data and joints into arrays from vectors to pass into generation.
//	float fHexVertexData[32];
//
//	for (int i = 0; i < 32; i++)
//	{
//		fHexVertexData[i] = m_fVecVertexData[i];
//	}
//
//	unsigned int uiHexIndices[6];
//
//	for (int i = 0; i < 6; i++)
//	{
//		uiHexIndices[i] = m_uiVecTriIndices[i];
//	}
//
//	//Generate the VAO.
//	glGenVertexArrays(1, &m_uiVAO);
//	glBindVertexArray(m_uiVAO);
//
//	//Generate the EBO.
//	glGenBuffers(1, &m_uiEBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiHexIndices), uiHexIndices, GL_STATIC_DRAW);
//
//	//Generate the VBO.
//	glGenBuffers(1, &m_uiVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(fHexVertexData), fHexVertexData, GL_STATIC_DRAW);
//
//	//Set the Vertex Attribute information (position).
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	//Set the Vertex Attribute information (colour).
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	//Set the Vertex Attribute information (tex coords).
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//}