#include "SceneManager.h"

CSkybox* CSceneManager::m_poSkybox = nullptr;
std::vector<CModel*> CSceneManager::m_oVecModelPtrs;

void CSceneManager::CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram)
{
	CModel* poModel = new CModel(_sModelFilePath, _oVecTextureFilePaths, _uiProgram);
	m_oVecModelPtrs.push_back(poModel);
}

void CSceneManager::CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition)
{
	CModel* poModel = new CModel(_sModelFilePath, _oVecTextureFilePaths, _uiProgram, _v3fPosition);
	m_oVecModelPtrs.push_back(poModel);
}

void CSceneManager::CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation)
{
	CModel* poModel = new CModel(_sModelFilePath, _oVecTextureFilePaths, _uiProgram, _v3fPosition, _v3fRotation);
	m_oVecModelPtrs.push_back(poModel);
}

void CSceneManager::CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale)
{
	CModel* poModel = new CModel(_sModelFilePath, _oVecTextureFilePaths, _uiProgram, _v3fPosition, _v3fRotation, _v3fScale);
	m_oVecModelPtrs.push_back(poModel);
}

void CSceneManager::CreateSkybox(std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram)
{
	m_poSkybox = new CSkybox(_uiProgram, _oVecTextureFilePaths);
}

std::vector<CModel*>* CSceneManager::GetModels()
{
	return &m_oVecModelPtrs;
}

CSkybox* CSceneManager::GetSkybox()
{
	return m_poSkybox;
}

void CSceneManager::Update()
{
	for (size_t i = 0; i < m_oVecModelPtrs.size(); i++)
	{
		m_oVecModelPtrs[i]->Update();
	}
}

void CSceneManager::Render()
{
	CCamera* poCamera = CCamera::GetMainCamera();

	for (size_t i = 0; i < m_oVecModelPtrs.size(); i++)
	{
		m_oVecModelPtrs[i]->Render(m_poSkybox, poCamera);
	}

	m_poSkybox->Render(poCamera);
}

void CSceneManager::DestroyScene()
{
	delete m_poSkybox;

	for (size_t i = 0; i < m_oVecModelPtrs.size(); i++)
	{
		delete m_oVecModelPtrs[i];
	}
}