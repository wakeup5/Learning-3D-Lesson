#include "stdafx.h"
#include "Scene1.h"

namespace NS_ROOT
{
	namespace NS_BASE
	{
		using namespace Objects;

		Scene1::Scene1()
		{

		}
		Scene1::~Scene1()
		{

		}

		HRESULT Scene1::Setup()
		{
			_vertex[0] = PC_VERTEX(-1, -1, 0, D3DCOLOR_XRGB(0, 255, 255));
			_vertex[1] = PC_VERTEX(-1, 1, 0, D3DCOLOR_XRGB(255, 0, 255));
			_vertex[2] = PC_VERTEX(1, 1, 0, D3DCOLOR_XRGB(255, 255, 0));
			_vertex[3] = PC_VERTEX(-1, -1, 0, D3DCOLOR_XRGB(0, 255, 255));
			_vertex[4] = PC_VERTEX(1, 1, 0, D3DCOLOR_XRGB(255, 0, 255));
			_vertex[5] = PC_VERTEX(1, -1, 0, D3DCOLOR_XRGB(255, 0, 255));

			DEVICE->SetRenderState(D3DRS_LIGHTING, false);

			_camera = new Camera;
			_camera->SetAutoUpdate(true);
			_camera->MovePositionWorld(D3DXVECTOR3(0, 5, -10));

			return S_OK;
		}
		void Scene1::Release()
		{
			((*_camera).Camera::SetAutoUpdate)(true);
			SAFE_DELETE(_camera);
		}
		void Scene1::Update(float timeDelta)
		{
			_camera->DefaultControl(timeDelta);
			_camera->UpdateCamToDevice(DEVICE);
		}
		void Scene1::Render()
		{
			DEVICE->SetFVF(PC_VERTEX::FVF);
			DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, _vertex, sizeof(PC_VERTEX));
		}
		LRESULT Scene1::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
		{

			return DefWindowProc(hWnd, iMessage, wParam, lParam);
		}
	}
}