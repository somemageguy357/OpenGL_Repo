/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Quad.h
Description : Inheriting from Shape.h: sets up the shape with quad vertex data.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Shape.h"

class CQuad : public CShape
{
public:
	CQuad();
	CQuad(TVector3f _v3fPosition);
	CQuad(TVector3f _v3fPosition, TVector3f _v3fRotation);
	CQuad(TVector3f _v3fPosition, TVector3f _v3fRotation, TVector3f _v3fScale);
	~CQuad();

private:
	void ShapeSetup() override;

	void SetVertexData() override;

	void SetTriIndices() override;
};