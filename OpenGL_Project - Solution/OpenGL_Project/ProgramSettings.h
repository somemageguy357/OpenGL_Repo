#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

class CProgramSettings
{
public:
	static void Update();

	static void SetWireframe(bool _bOn);

	static void SetFaceCulling(bool _bOn);

	static void SetDepthTesting(bool _bOn);

	static void SetTextureBlending(bool _bOn);

private:
	static bool m_bWireframeOn;
	static bool m_bFaceCullingOn;
	static bool m_bDepthTestingOn;
	static bool m_bTextureBlendingOn;

	CProgramSettings() {};
	~CProgramSettings() {};

	static void ToggleWireframe();

	static void ToggleFaceCulling();
};