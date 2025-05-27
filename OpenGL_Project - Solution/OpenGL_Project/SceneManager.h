#pragma once
#include "Model.h"
#include "Skybox.h"

class CSceneManager
{
public:
	static void CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram);
	static void CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition);
	static void CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation); 
	static void CreateModel(std::string _sModelFilePath, std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram, glm::vec3 _v3fPosition, glm::vec3 _v3fRotation, glm::vec3 _v3fScale);

	static void CreateSkybox(std::vector<std::string> _oVecTextureFilePaths, GLuint _uiProgram);

	static std::vector<CModel*>* GetModels();

	static CSkybox* GetSkybox();

	static void Update();

	static void Render();

	static void DestroyScene();

private:
	static CSkybox* m_poSkybox;

	static std::vector<CModel*> m_oVecModelPtrs;

	CSceneManager() = delete;
	~CSceneManager() = delete;
};