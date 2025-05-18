#include "Model.h"
#include "ModelMesh.h"
#include "Camera.h"
#include "TimeManager.h"
#include "LightingSettings.h"

#include <iostream>

CModel::CModel(std::string _sFilePath, CSkybox* _poSkybox) : CShape()
{
	m_poMesh = new CModelMesh(_sFilePath);
	m_poSkybox = _poSkybox;
}

CModel::~CModel()
{
	delete m_poMesh;
}

void CModel::Render(GLuint _uiProgram)
{
	glUseProgram(_uiProgram);

	//Supplies the programs current lifetime to the shader program (if it requires it).
	//GLint iCurrentTimeLocation = glGetUniformLocation(_uiProgram, "fCurrentTime");
	//glUniform1f(iCurrentTimeLocation, CTimeManager::GetCurrentTime());

	glBindVertexArray(*m_poMesh->GetVAO());

	//Bind the shape's textures (if any).
	BindTextures(_uiProgram);

	glUniform1i(glGetUniformLocation(_uiProgram, "oSkyboxTexture"), *m_poSkybox->GetTextureID());

	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matModel"), 1, GL_FALSE, glm::value_ptr(*m_oTransform.GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matView"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(_uiProgram, "matProjection"), 1, GL_FALSE, glm::value_ptr(*CCamera::GetMainCamera()->GetProjectionMatrix()));
	glUniform3fv(glGetUniformLocation(_uiProgram, "v3fCameraPosition"), 1, glm::value_ptr(*CCamera::GetMainCamera()->GetTransform()->GetPosition()));

	glUniform1f(glGetUniformLocation(_uiProgram, "fAmbientStrength"), CLightingSettings::GetAmbientStrength());
	glUniform3fv(glGetUniformLocation(_uiProgram, "v3fAmbientColour"), 1, glm::value_ptr(*CLightingSettings::GetAmbientColour()));

	glUniform1f(glGetUniformLocation(_uiProgram, "fSpecularStrength"), 0.0f);
	glUniform1f(glGetUniformLocation(_uiProgram, "fObjectShineValue"), 32.0f);

	glDrawArrays(GL_TRIANGLES, 0, m_poMesh->GetTriIndices()->size());

	glBindVertexArray(0);
	glUseProgram(0);
}