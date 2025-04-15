/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : TimeManager.h
Description : Contains the programs current and delta time values.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

//Static class that holds the program's current/run time and delta time values.
class CTimeManager
{
public:
	/// <summary>
	/// Sets the value of the program's DeltaTime.
	/// </summary>
	/// <param name="_fDeltaTime:">The new value of DeltaTime.</param>
	static void SetDeltaTime(float _fDeltaTime);

	/// <summary>
	/// Sets the value of the program's CurrentTime (run time).
	/// </summary>
	/// <param name="_fCurrentTime:">The new value of CurrentTime.</param>
	static void SetCurrentTime(float _fCurrentTime);

	/// <summary>
	/// Returns the program's DeltaTime.
	/// </summary>
	static float GetDeltaTime();

	/// <summary>
	/// Returns the program's CurrentTime.
	/// </summary>
	/// <returns></returns>
	static float GetCurrentTime();

private:
	static float m_fDeltaTime;
	static float m_fCurrentTime;

	CTimeManager();
	~CTimeManager();
};