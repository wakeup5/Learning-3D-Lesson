#pragma once
class GameMain
{
private:
	Scene* m_Scene;
public:
	GameMain();
	~GameMain();

	//����
	HRESULT Init(void);

	//����
	void Release();

	//������Ʈ
	void Update();

	//��ο�
	void Draw();

public:

	//���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};