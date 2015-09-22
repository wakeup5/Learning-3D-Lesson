#include "stdafx.h"
#include "Scene_15_09_21.h"

DWORD S15_09_21::Woman::_lightIndex = 10;

Scene_15_09_21::Scene_15_09_21()
{
}


Scene_15_09_21::~Scene_15_09_21()
{
}

HRESULT Scene_15_09_21::Setup()
{
	SetRandomSeed();

	_cam = new Camera;
	//_cam->SetWorldPosition({ 0, 5, 10 });
	//_cam->LookPosition({ 0, 0, 0 });

	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	for (int i = 0; i < 3; i++)
	{
		_woman[i] = new S15_09_21::Woman;
	}
	return S_OK;
}
void Scene_15_09_21::Release()
{
	//SAFE_RELEASE(m_pRootRun);
	//SAFE_RELEASE(m_pRootSt);
}
void Scene_15_09_21::Update(float timeDelta)
{
	for (int i = 0; i < 3; i++)
	{
		_woman[i]->Update();
	}

	_cam->SetDeviceView(DEVICE);
	_cam->UpdateCamToDevice(DEVICE);

	_cam->DefaultControl(timeDelta);

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			_woman[i]->Click();
		}
	}
	
	D3DXVECTOR3 poly[2][3] = { {{-10, 0, -10}, {-10, 0, 10}, {10, 0, 10}}, {{-10, 0, -10}, {10, 0, 10}, {10, 0, -10}} };
	POINT m = GetMousePos();
	Ray r = GetRayByMousePos(m.x, m.y);
	D3DXVECTOR3 temp;

	if (KEY_MGR->IsOnceDown('1'))
	{
		if (IntersectPolygon(r, poly[0], &temp) || IntersectPolygon(r, poly[1], &temp))
		{
			_woman[0]->MoveTo(temp);
		}
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		if (IntersectPolygon(r, poly[0], &temp) || IntersectPolygon(r, poly[1], &temp))
		{
			_woman[1]->MoveTo(temp);
		}
	}
	if (KEY_MGR->IsOnceDown('3'))
	{
		if (IntersectPolygon(r, poly[0], &temp) || IntersectPolygon(r, poly[1], &temp))
		{
			_woman[2]->MoveTo(temp);
		}
	}
}
void Scene_15_09_21::Render()
{
	for (int i = 0; i < 3; i++)
	{
		_woman[i]->Render();
	}
}
