/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ModelMesh.cpp
Description : Contains function definitions for ModelMesh.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

//#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "ModelMesh.h"

#include <iostream>

CModelMesh::CModelMesh(std::string _sFilePath, glm::vec3 _v3fColour)
{
	std::vector<VertexStandard> oVecVertices;
	tinyobj::ObjReaderConfig oReaderConfig;
	tinyobj::ObjReader oReader;

	if (oReader.ParseFromFile(_sFilePath, oReaderConfig) == false)
	{
		if (oReader.Error().empty() == false)
		{
			std::cerr << "TinyObjReader: " << oReader.Error();
		}

		exit(1);
	}

	if (oReader.Warning().empty() == false)
	{
		std::cout << "TinyObjReader: " << oReader.Warning();
	}

	auto& aAttrib = oReader.GetAttrib();
	auto& aShapes = oReader.GetShapes();

	for (size_t iShapeIndex = 0; iShapeIndex < aShapes.size(); iShapeIndex++)
	{
		size_t iReadIndexOffset = 0;

		for (size_t iFaceIndex = 0; iFaceIndex < aShapes[iShapeIndex].mesh.num_face_vertices.size(); iFaceIndex++)
		{
			size_t iFaceVertexCount = size_t(aShapes[iShapeIndex].mesh.num_face_vertices[iFaceIndex]);

			for (size_t iVertexIndex = 0; iVertexIndex < iFaceVertexCount; iVertexIndex++)
			{
				VertexStandard oVertex{};
				tinyobj::index_t iTinyObjVertex = aShapes[iShapeIndex].mesh.indices[iReadIndexOffset + iVertexIndex];

				oVertex.v3fPosition =
				{
					aAttrib.vertices[3 * size_t(iTinyObjVertex.vertex_index) + 0],
					aAttrib.vertices[3 * size_t(iTinyObjVertex.vertex_index) + 1],
					aAttrib.vertices[3 * size_t(iTinyObjVertex.vertex_index) + 2],
				};

				oVertex.v3fColour = _v3fColour;

				if (iTinyObjVertex.texcoord_index >= 0)
				{
					oVertex.v2fTexCoord =
					{
						aAttrib.texcoords[2 * size_t(iTinyObjVertex.texcoord_index) + 0],
						aAttrib.texcoords[2 * size_t(iTinyObjVertex.texcoord_index) + 1],
					};
				}

				if (iTinyObjVertex.normal_index >= 0)
				{
					oVertex.v3fNormals =
					{
						aAttrib.normals[3 * size_t(iTinyObjVertex.normal_index) + 0],
						aAttrib.normals[3 * size_t(iTinyObjVertex.normal_index) + 1],
						aAttrib.normals[3 * size_t(iTinyObjVertex.normal_index) + 2],
					};
				}

				oVecVertices.push_back(oVertex);
			}

			iReadIndexOffset += iFaceVertexCount;
		}
	}

	m_iDrawType = GL_TRIANGLES;
	m_uiDrawCount = (GLuint)oVecVertices.size();
	m_oVecTriIndices.resize(m_uiDrawCount);

	int iInstanceCount = 1;
	bool bExistingVAOFound = GetExistingVAOInstance(_sFilePath, &m_uiVAO, &iInstanceCount);

	if (bExistingVAOFound == false)
	{
		glGenVertexArrays(1, &m_uiVAO);
	}

	glBindVertexArray(m_uiVAO);
	
	if (bExistingVAOFound == false)
	{
		AddVAOInstance(_sFilePath, m_uiVAO);
	}

	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStandard) * oVecVertices.size(), oVecVertices.data(), GL_STATIC_DRAW);

	GLuint uiInstancedVBO;
	glGenBuffers(1, &uiInstancedVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiInstancedVBO);
	glBufferData(GL_ARRAY_BUFFER, iInstanceCount * sizeof(glm::mat4), oVecVertices.data(), GL_DYNAMIC_DRAW);

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

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);

	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
}

CModelMesh::~CModelMesh() {}