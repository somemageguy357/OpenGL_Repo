/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : WindowManager.cpp
Description : Contains function definitions for WindowManager.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "WindowManager.h"

int CWindowManager::m_iWidth = 0;
int CWindowManager::m_iHeight = 0;

void CWindowManager::SetWidth(int _iWidth)
{
	m_iWidth = _iWidth;
}

int CWindowManager::GetWidth()
{
	return m_iWidth;
}

void CWindowManager::SetHeight(int _iHeight)
{
	m_iHeight = _iHeight;
}

int CWindowManager::GetHeight()
{
	return m_iHeight;
}

void CWindowManager::SetSize(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;
}