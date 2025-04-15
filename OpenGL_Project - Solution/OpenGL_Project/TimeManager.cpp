/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : TimeManager.cpp
Description : Contains function definitions for TimeManager.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "TimeManager.h"

float CTimeManager::m_fDeltaTime = 0.0f;
float CTimeManager::m_fCurrentTime = 0.0f;

CTimeManager::CTimeManager() {}

CTimeManager::~CTimeManager() {}

void CTimeManager::SetDeltaTime(float _fDeltaTime)
{
	m_fDeltaTime = _fDeltaTime;
}

void CTimeManager::SetCurrentTime(float _fCurrentTime)
{
	m_fCurrentTime = _fCurrentTime;
}

float CTimeManager::GetDeltaTime()
{
	return m_fDeltaTime;
}

float CTimeManager::GetCurrentTime()
{
	return m_fCurrentTime;
}