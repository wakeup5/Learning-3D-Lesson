#include "stdafx.h"
#include "Scene_15_09_21.h"


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
	_cam->SetWorldPosition({ 0, 5, 10 });
	_cam->LookPosition({ 0, 0, 0 });

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

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

}
void Scene_15_09_21::Render()
{
	for (int i = 0; i < 3; i++)
	{
		_woman[i]->Render();
	}
}
