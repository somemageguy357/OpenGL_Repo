/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ComponentBehaviour.h
Description : Base class for "component behaviours". Component behaviours are to be attached to specific objects, such as a movement
				based class/script, where only that one object will perform its functions. 
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#ifndef CB
#define CB
#include "Transform.h"

class CComponentBehaviour
{
public:
	//Run every frame, overriden from deriving ComponentBehaviour classes.
	virtual void Update(CTransform* _poTransform) = 0;

protected:
	CComponentBehaviour();
	~CComponentBehaviour();
};
#endif