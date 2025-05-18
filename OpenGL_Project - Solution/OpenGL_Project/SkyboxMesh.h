#pragma once
#include "Mesh.h"
#include <string>

class CSkyboxMesh : public CMesh
{
public:
	CSkyboxMesh(std::string _sFilePath);
	~CSkyboxMesh();

private:
	GLuint m_uiDrawCount = 0;
	int m_iDrawType = 0;

	//Wraps the generative functions of the mesh. Called from the mesh's constructors.
	void MeshSetup() override;

	//Generates the default vertex data of the particular mesh.
	void GenerateVertexData() override;

	//Generates the default tri indice data of the particular mesh.
	void GenerateTriIndices() override;

	//Generates the mesh's render data (buffers, vertex pointers, etc).
	void GenerateMesh() override;
};