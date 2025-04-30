#include "Model.h"
#include "ModelMesh.h"
#include "Camera.h"
#include "TimeManager.h"

CModel::CModel(std::string _sFilePath) : CShape()
{
	m_poMesh = new CModelMesh(_sFilePath);
}

CModel::~CModel()
{
	delete m_poMesh;
}

void CModel::Render(GLuint _uiProgram)
{
	glUseProgram(_uiProgram);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*GetMesh()->GetVAO());

	//Bind the shape's textures (if any).
	BindTextures(_uiProgram);

	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*GetTransform()->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetProjectionMatrix()));

	glDrawArrays(GL_TRIANGLES, 0, GetMesh()->GetTriIndices()->size());

	glBindVertexArray(0);
	glUseProgram(0);
}