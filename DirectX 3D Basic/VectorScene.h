#pragma once
#include "Scene.h"
class VectorScene : public Scene
{
public:
	VectorScene();
	virtual ~VectorScene();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual LRESULT WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

