#include "Shape.h"

class CModel : public CShape
{
public:
	CModel(std::string _sFilePath);
	~CModel();

	void Render(GLuint _uiProgram) override;

private:

};