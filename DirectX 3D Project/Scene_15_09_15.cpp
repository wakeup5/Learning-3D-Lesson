#include "stdafx.h"
#include "Scene_15_09_15.h"


Scene_15_09_15::Scene_15_09_15()
{
}


Scene_15_09_15::~Scene_15_09_15()
{
}


HRESULT Scene_15_09_15::Setup()
{
	cAseLoader l;
	m_pRootFrame = l.Load("woman/woman_01_all.ASE");

	cObjLoader ol;
	ol.Load(m_vecGroup, "obj", "map.obj");

	_om = new cObjMap("obj", "map.obj", NULL);
	
	_camera = new NS_ROOT::NS_OBJECTS::Camera;
	_camera->SetAutoUpdate(true);
	_camera->MovePositionWorld(D3DXVECTOR3(0, 5, -10));

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	_posWoman = D3DXVECTOR3(0, 0, 0);
	_dirWoman = D3DXVECTOR3(0, 0, 0);
	_cRot = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIXA16 matWorld, matS, matR;

	D3DXMatrixScaling(&matS, 0.02, 0.02, 0.02);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	for (int i = 0; i < _om->m_vecSurface.size(); i++)
	{
		D3DXVec3TransformCoord(&_om->m_vecSurface[i], &_om->m_vecSurface[i], &matWorld);
	}

	return S_OK;
}
void Scene_15_09_15::Release()
{
	SAFE_DELETE(_camera);
	m_pRootFrame->Release();
	delete m_pRootFrame;
}
void Scene_15_09_15::Update(float timeDelta)
{
	D3DXMATRIXA16 totalMat, transMat, rotMat;
	D3DXMatrixTranslation(&transMat, _posWoman.x, _posWoman.y, _posWoman.z);
	D3DXMatrixRotationY(&rotMat, _dirWoman.y);
	totalMat = rotMat * transMat;

	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&direction, &direction, &rotMat);

	D3DXVECTOR3 nextM = _posWoman - (direction / 10);

	if (_om->GetHeight(nextM.x, nextM.y, nextM.z))
	{
		if (KEY_MGR->IsStayDown('W'))
		{
			_posWoman -= (direction / 10);
		}
		if (KEY_MGR->IsStayDown('S'))
		{
			_posWoman += (direction / 10);
		}

		_posWoman.y = nextM.y;
	}

	if (KEY_MGR->IsStayDown('A'))
	{
		_dirWoman.y -= RAD(5);
	}
	if (KEY_MGR->IsStayDown('D'))
	{
		_dirWoman.y += RAD(5);
	}

	if (m_pRootFrame)
	{
		int nKeyFrame = (GetTickCount() * 10) % (3200 - 640) + 640;
		m_pRootFrame->Update(nKeyFrame, &totalMat);
	}

	if (KEY_MGR->IsStayDown(VK_LEFT))
	{
		_cRot.y -= RAD(5);
	}
	if (KEY_MGR->IsStayDown(VK_RIGHT))
	{
		_cRot.y += RAD(5);
	}

	D3DXVECTOR3 cd = D3DXVECTOR3(0, 5, 10);
	D3DXMATRIXA16 cry, crx, cr;
	D3DXMatrixRotationY(&cry, _cRot.y);
	D3DXMatrixRotationX(&crx, -_cRot.x);
	cr = cry * crx;
	D3DXVec3TransformCoord(&cd, &cd, &cr);

	_camera->SetWorldPosition(_posWoman + cd);
	_camera->LookPosition(_posWoman);
	_camera->UpdateCamToDevice(DEVICE);
}
void Scene_15_09_15::Render()
{
	m_pRootFrame->Render();

	D3DXMATRIXA16 matWorld, matS, matR;

	D3DXMatrixScaling(&matS, 0.02, 0.02, 0.02);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;

	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
