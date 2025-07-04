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
#include "Camera.h"

#include <iostream>

CQuad::CQuad() : CObject() 
{
	ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition) : CObject(_v3fPosition)
{
	ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation) : CObject(_v3fPosition, _v3fRotation)
{
	ShapeSetup();
}

CQuad::CQuad(glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale) : CObject(_v3fPosition, _v3fRotation, _v3fScale)
{
	ShapeSetup();
}

CQuad::~CQuad() {}

void CQuad::Render(CSkybox* _poSkybox, CCamera* _poCamera)
{
	glUseProgram(m_poProgram->uiID);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	//GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(m_uiVAO);

	//Bind the Object's textures (if any).
	BindTextures(m_poProgram->uiID);

	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matView"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(m_poProgram->uiID, "matProjection"), 1, GL_FALSE, glm::value_ptr(*_poCamera->GetProjectionMatrix()));

	glDrawElements(GL_TRIANGLES, (GLsizei)m_oVecTriIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void CQuad::ShapeSetup()
{
	GenerateVertexData();
	GenerateTriIndices();
	GenerateShape();
}

void CQuad::GenerateVertexData()
{
	//Positions and colours of the quad's vertices.
	std::vector<float> fVecVertexData =
	{
		//Positions							//Colours				//Tex Coords (x, y)
		-100.0f,		100.0f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		100.0f,		100.0f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		100.0f,		-100.0f,		0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		-100.0f,		-100.0f,		0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
	};

	m_oVecVertexData.insert(m_oVecVertexData.end(), fVecVertexData.begin(), fVecVertexData.end());
}

std::vector<float>* CQuad::GetVertexData()
{
	return &m_oVecVertexData;
}

std::vector<unsigned int>* CQuad::GetTriIndices()
{
	return &m_oVecTriIndices;
}

void CQuad::GenerateTriIndices()
{
	//Indices of the vertices for the triangles that make up the quad.
	std::vector<unsigned int> uiVecTriIndices =
	{
		0, 1, 2,
		0, 2, 3,
	};

	m_oVecTriIndices.insert(m_oVecTriIndices.end(), uiVecTriIndices.begin(), uiVecTriIndices.end());
}

void CQuad::GenerateShape()
{
	//Converting the quads's vertex data and joints into arrays from vectors to pass into generation.
	float fHexVertexData[32];

	for (int i = 0; i < 32; i++)
	{
		fHexVertexData[i] = m_oVecVertexData[i];
	}

	unsigned int uiHexIndices[6];

	for (int i = 0; i < 6; i++)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set the Vertex Attribute information (colour).
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Set the Vertex Attribute information (tex coords).
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}