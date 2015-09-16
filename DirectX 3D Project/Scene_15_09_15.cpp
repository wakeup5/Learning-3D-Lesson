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

	//텍스쳐들
	LPDIRECT3DTEXTURE9 t1, t2, t3;
	D3DXCreateTextureFromFile(DEVICE, "./obj/Map__21_Normal_Bump.tga", &t1);
	D3DXCreateTextureFromFile(DEVICE, "./obj/WS_Canon_01_S.tga", &t2);
	D3DXCreateTextureFromFile(DEVICE, "./obj/box.jpg", &t3);

	_tex[0] = t1;
	_tex[1] = t2;
	_tex[2] = t3;

	for (int i = 0; i < 10; i++)
	{
		_cubes[i] = NULL;
	}
	_cubes[0] = new NS_ROOT::NS_OBJECTS::Cube;
	_cubes[0]->Setup(_tex[NS_ROOT::NS_UTIL::RandomIntRange(0, 3)]);

	NS_ROOT::NS_UTIL::SetRandomSeed();
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	DEVICE->SetSamplerState(0,
		D3DSAMP_ADDRESSU,		//U 가로 진행 방식 설정
		D3DTADDRESS_CLAMP);
	DEVICE->SetSamplerState(0,
		D3DSAMP_ADDRESSV,		//V 세로 진행 방식 설정
		D3DTADDRESS_WRAP);

	return S_OK;
}
void Scene_15_09_15::Release()
{
	SAFE_DELETE(_camera);
	m_pRootFrame->Release();
	//delete m_pRootFrame;
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


	//큐브들
	for (int i = 0; i < 10; i++)
	{
		if (_cubes[i] != NULL) continue;

		//if (NS_ROOT::NS_UTIL::RandomFloatRange(0, 1) < 0.01)
		{
			D3DXVECTOR3 pos(0, 0, 0);
			//do
			{
				pos.x = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 100);
				pos.y = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 100);
				pos.z = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 100);
			} 
			
			if (!_om->GetHeight(pos.x, pos.y, pos.z)) continue;
			pos.y += 1;
			_cubes[i] = new NS_ROOT::NS_OBJECTS::Cube;
			_cubes[i]->Setup(_tex[NS_ROOT::NS_UTIL::RandomIntRange(0, 3)]);

			_cubes[i]->SetWorldPosition(pos);

			_cubes[i]->SetScale(0.25, 0.25, 0.25);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (_cubes[i] != NULL)
		{
			float distance = NS_ROOT::NS_UTIL::GetDistance(_cubes[i]->GetWorldPosition(), _posWoman);
			if (distance < 2.4)
			{
				SAFE_RELEASE(_cubes[i]);
				_score += 100;
				continue;
			}

			_cubes[i]->Update();
		}
	}

}
void Scene_15_09_15::Render()
{
	m_pRootFrame->Render();

	D3DXMATRIXA16 matWorld, matS, matR;

	DEVICE->SetTexture(0, NULL);

	D3DXMatrixScaling(&matS, 0.02, 0.02, 0.02);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;

	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}

	for (int i = 0; i < 10; i++)
	{
		if (_cubes[i] != NULL)
		{
			_cubes[i]->Render();
		}
	}
	DEVICE->SetTexture(0, NULL);
	
	DXFONT_MGR->PrintText(std::to_string(_score), 10, 200, 0xff000000);
}
