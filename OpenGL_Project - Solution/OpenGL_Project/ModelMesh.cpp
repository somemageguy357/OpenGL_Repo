#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "ModelMesh.h"

#include <iostream>

CModelMesh::CModelMesh(std::string _sFilePath)
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

				if (iTinyObjVertex.texcoord_index >= 0)
				{
					oVertex.v2fTexCoord =
					{
						aAttrib.texcoords[2 * size_t(iTinyObjVertex.texcoord_index) + 0],
						aAttrib.texcoords[2 * size_t(iTinyObjVertex.texcoord_index) + 1],
					};
				}

				//if (iTinyObjVertex.normal_index >= 0)
				//{
				//	//normal part
				//}

				oVecVertices.push_back(oVertex);
			}

			iReadIndexOffset += iFaceVertexCount;
		}
	}

	m_iDrawType = GL_TRIANGLES;
	m_uiDrawCount = (GLuint)oVecVertices.size();
	m_oVecTriIndices.resize(m_uiDrawCount);

	GLuint uiVBO;
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);
	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStandard) * oVecVertices.size(), oVecVertices.data(), GL_STATIC_DRAW);

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

CModelMesh::~CModelMesh()
{

}

void CModelMesh::MeshSetup()
{
}

void CModelMesh::GenerateVertexData()
{
}

void CModelMesh::GenerateTriIndices()
{
}

void CModelMesh::GenerateMesh()
{
}