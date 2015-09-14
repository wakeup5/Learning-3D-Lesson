#include "stdafx.h"
#include "GameMain.h"
#include "Scene1.h"

namespace NS_ROOT
{
	namespace NS_BASE
	{
		GameMain::GameMain()
			: _scene(NULL)
		{
		}

		GameMain::~GameMain()
		{
		}

		HRESULT GameMain::Setup()
		{
			DEVICEMANAGER->Setup();
			TIME_MGR->Setup();
			KEY_MGR->Setup();
			LOG_MGR->Setup(LOG_WINDOW | LOG_FILE, g_hWnd, "Dump");
			DXFONT_MGR->Setup(DEVICE);
			GIZMO_MGR->Setup(DEVICE);

			_scene = new Scene1;
			_scene->Setup();

			return S_OK;
		}

		void GameMain::Release()
		{
			SAFE_RELEASE(_scene);

			NS_ROOT::DirectX::Device::ReleaseInstance();
			NS_ROOT::DirectX::GizmoManager::ReleaseInstance();
			NS_ROOT::DirectX::DXFontManager::ReleaseInstance();
			NS_ROOT::Util::TimeMgr::ReleaseInstance();
			NS_ROOT::Util::KeyMgr::ReleaseInstance();
			NS_ROOT::Util::LogMgr::ReleaseInstance();
		}

		void GameMain::Update()
		{
			TIME_MGR->UpdateTime(60.0f);
			if (_scene) _scene->Update(TIME_MGR->GetFrameDeltaSec());
		}

		void GameMain::Render()
		{
			HRESULT result = 
				DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
					BG_COLOR, 1.0f, 0);

			if (SUCCEEDED(result))
			{
				DEVICE->BeginScene();
#ifdef _DEBUG
				TIME_MGR->DrawTimeInfo();
				GIZMO_MGR->WorldGrid(1, 10);
#endif
				if(_scene) _scene->Render();

				DEVICE->EndScene();
				DEVICE->Present(NULL, NULL, NULL, NULL);
			}
		}

		LRESULT CALLBACK GameMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (_scene)
			{
				return _scene->WndProc(hWnd, message, wParam, lParam);
			}

			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}//end NS_BASE
}//end NS_ROOT