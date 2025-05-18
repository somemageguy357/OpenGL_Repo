#ifndef CB
#define CB

class CShape; //Forward declaration.

class CComponentBehaviour
{
public:
	virtual void Update(CShape* _poShape) = 0;

protected:
	CComponentBehaviour();
	~CComponentBehaviour();
};
#endif