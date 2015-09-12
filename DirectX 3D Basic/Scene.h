#pragma once
class Scene
{
public:
	Scene(){}
	virtual ~Scene(){}

	virtual void Setup() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual LRESULT WinProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;
};

