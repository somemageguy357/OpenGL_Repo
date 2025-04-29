#include "Mesh.h"

class CCubeMesh : public CMesh
{
public:
	static CCubeMesh* GetInstance()
	{
		if (m_poInstance == nullptr)
		{
			m_poInstance = new CCubeMesh();
		}

		return m_poInstance;
	}

private:
	static CCubeMesh* m_poInstance;

	CCubeMesh();
	~CCubeMesh();

	//Wraps the generative functions of the mesh. Called from the mesh's constructors.
	void MeshSetup() override;

	//Generates the default vertex data of the particular mesh.
	void GenerateVertexData() override;

	//Generates the default tri indice data of the particular mesh.
	void GenerateTriIndices() override;

	//Generates the mesh's render data (buffers, vertex pointers, etc).
	void GenerateMesh() override;
};