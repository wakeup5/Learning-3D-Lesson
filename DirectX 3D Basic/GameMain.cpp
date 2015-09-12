#include "stdafx.h"
#include "GameMain.h"
#include "VectorScene.h"

GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

HRESULT GameMain::Init(void)
{
	m_Scene = new VectorScene;

	return S_OK;
}

void GameMain::Release()
{
	if (m_Scene)
		SAFE_RELEASE(m_Scene);
}

void GameMain::Update()
{
	if (m_Scene)
		m_Scene->Update();
}

void GameMain::Draw()
{
	if (m_Scene)
		m_Scene->Render();
}

HRESULT GameMain::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
	case WM_DESTROY:			//�����찡 �ı��ȴٸ�..
		PostQuitMessage(0);		//���α׷� ���� ��û ( �޽��� ������ ���������� �ȴ� )
		break;
	}

	if (m_Scene)
	{
		return m_Scene->WinProc(hWnd, iMessage, wParam, lParam);
	}
	else
	{
		return DefWindowProc( hWnd, iMessage, wParam, lParam );
	}
}