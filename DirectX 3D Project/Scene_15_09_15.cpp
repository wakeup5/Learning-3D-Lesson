#include "stdafx.h"
#include "Scene_15_09_15.h"

using namespace NS_ROOT;

Scene_15_09_15::Scene_15_09_15()
{
}


Scene_15_09_15::~Scene_15_09_15()
{
}


HRESULT Scene_15_09_15::Setup()
{
	cAseLoader l;
	m_pRootRun = l.Load("woman/woman_01_all.ASE");
	m_pRootSt = l.Load("woman/woman_01_all_stand.ASE");

	m_pRootFrame = m_pRootSt;

	cObjLoader ol;
	ol.Load(m_vecGroup, "obj", "map.obj");

	D3DXMATRIXA16 matS, matR;
	D3DXMatrixScaling(&matS, 0.02, 0.02, 0.02);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;

	_om = new cObjMap("obj", "map_surface.obj", &matWorld);
	
	_camera = new NS_ROOT::NS_OBJECTS::Camera;
	_camera->SetAutoUpdate(true);
	_camera->MovePositionWorld(D3DXVECTOR3(0, 5, -10));

	_posWoman = D3DXVECTOR3(0, 0, 0);
	_dirWoman = D3DXVECTOR3(0, 0, 0);
	_cRot = D3DXVECTOR3(0, 0, 0);
	_look = { 0, 10, 0 };

	//텍스쳐들
	D3DXCreateTextureFromFile(DEVICE, "./obj/Map__21_Normal_Bump.tga", &_tex[0]);
	D3DXCreateTextureFromFile(DEVICE, "./obj/WS_Canon_01_S.tga", &_tex[1]);
	D3DXCreateTextureFromFile(DEVICE, "./obj/box.jpg", &_tex[2]);

	D3DXCreateTextureFromFile(DEVICE, "./resource/batman.png", &_tBat);

	for (int i = 0; i < 10; i++)
	{
		_cubes[i] = NULL;
	}
	for (int i = 0; i < 10; i++)
	{
		_bullets[i] = NULL;
	}

	NS_ROOT::NS_UTIL::SetRandomSeed(); 
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	
	_char = new NS_ROOT::Objects::Charactor;
	
	ac = new Objects::ActionMoveBezier;
	ac->AddPoint(D3DXVECTOR3(-20, 3, -0));
	ac->AddPoint(D3DXVECTOR3(-0, 3, -10));
	ac->AddPoint(D3DXVECTOR3(-20, 3, -20));
	ac->AddPoint(D3DXVECTOR3(-0, 3, -30));
	ac->AddPoint(D3DXVECTOR3(-20, 3, -40));
	ac->SetActionTime(5.0f);
	ac->SetDeligate(_char);

	_char->SetAction(ac);
	ac->Start();

	return S_OK;
}
void Scene_15_09_15::Release()
{
	SAFE_DELETE(_camera);
	m_pRootFrame->Release();
	//delete m_pRootFrame;

	SAFE_DELETE(_char);
}
void Scene_15_09_15::Update(float timeDelta)
{
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

	_look = _look + (_posWoman - _look) / 20;

	_camera->SetWorldPosition(_look + cd);
	_camera->LookPosition(_look);
	_camera->ShakeUpdate(timeDelta);
	
	_camera->UpdateCamToDevice(DEVICE);
	

	KeyControl();
	CreateCube();
	CreateBullet();

	for (int i = 0; i < 10; i++)
	{
		if (_bullets[i] != NULL)
		{

			_bullets[i]->Update();

			if (_bullets[i]->_b) SAFE_RELEASE(_bullets[i]);
		}

	}

	for (int i = 0; i < 10; i++)
	{
		if (_cubes[i] != NULL)
		{
			float distance = D3DXVec3Length(&(_cubes[i]->GetWorldPosition() - _posWoman));
			if (distance < 2.4)
			{
				SAFE_RELEASE(_cubes[i]);
				_score += 100;
				continue;
			}

			_cubes[i]->Update();
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (_bullets[i] != NULL)
		{
			float distance = D3DXVec3Length(&(_bullets[i]->GetWorldPosition() - _char->GetWorldPosition()));
			if (distance < 2.4)
			{
				//SAFE_RELEASE(_char);
				_score += 100;

				_bullets[i]->_b = true;

				//_char = new Objects::Charactor;


				ac->ClearPoint();
				D3DXVECTOR3 pos;

				for (int i = 0; i < 5; i++)
				{
					pos.x = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 20);
					pos.y = 3;
					pos.z = NS_ROOT::NS_UTIL::RandomFloatRange(-50, 0);

					ac->AddPoint(pos);
				}

				//ac->SetDeligate(_char);

				//_char->SetAction(ac);
				ac->Start();

				_camera->ShakePos(0.5, 2.5);
				_camera->SetShakePosFlag(SHAKE_X | SHAKE_Y);

				break;
			}
		}
	}

	_char->Update();
}
void Scene_15_09_15::Render()
{
	m_pRootFrame->Render();


	DEVICE->SetTexture(0, NULL);
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

	for (int i = 0; i < 10; i++)
	{
		if (_bullets[i] != NULL) 
			_bullets[i]->Render();
	}

	DEVICE->SetTexture(0, _tBat);
	_char->Render();

	DEVICE->SetTexture(0, NULL);
	
	DXFONT_MGR->PrintText(std::to_string(_score), 10, 200, 0xff000000);
}

void Scene_15_09_15::KeyControl()
{
	D3DXMATRIXA16 totalMat, transMat, rotMat;
	D3DXMatrixTranslation(&transMat, _posWoman.x, _posWoman.y, _posWoman.z);
	D3DXMatrixRotationY(&rotMat, _dirWoman.y);
	totalMat = rotMat * transMat;

	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&direction, &direction, &rotMat);

	D3DXVECTOR3 nextM = _posWoman - (direction / 10);

	if (m_pRootFrame)
	{
		int nKeyFrame = (GetTickCount() * 10) % (3200 - 640) + 640;
		m_pRootFrame->Update(nKeyFrame, &totalMat);
	}

	if (_om->GetHeight(nextM.x, nextM.y, nextM.z))
	{
		if (KEY_MGR->IsStayDown('W'))
		{
			_posWoman -= (direction / 10);
			m_pRootFrame = m_pRootRun;
		}
		else if (KEY_MGR->IsStayDown('S'))
		{
			_posWoman += (direction / 10);
			m_pRootFrame = m_pRootRun;
		}
		else
		{
			m_pRootFrame = m_pRootSt;
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
}

void Scene_15_09_15::CreateCube()
{
	//큐브들
	for (int i = 0; i < 5; i++)
	{
		if (_cubes[i] != NULL) continue;

		D3DXVECTOR3 pos(0, 0, 0);

		pos.x = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 0);
		pos.y = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 0);
		pos.z = NS_ROOT::NS_UTIL::RandomFloatRange(-10, 0);

		if (!_om->GetHeight(pos.x, pos.y, pos.z)) continue;

		pos.y += 1;

		_cubes[i] = new NS_ROOT::NS_OBJECTS::Cube;
		_cubes[i]->Setup(_tex[NS_ROOT::NS_UTIL::RandomIntRange(0, 3)]);

		_cubes[i]->SetWorldPosition(pos);

		_cubes[i]->SetScale(0.25, 0.25, 0.25);
		_cubes[i]->SetBuffer();
	}
}

void Scene_15_09_15::CreateBullet()
{
	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		for (int i = 0; i < 10; i++)
		{
			if (_bullets[i] != NULL) continue;

			_bullets[i] = new NS_ROOT::NS_OBJECTS::Pyramid;
			_bullets[i]->Setup();
			_bullets[i]->SetWorldPosition(_posWoman.x, _posWoman.y + 1, _posWoman.z);
			_bullets[i]->angleY = _dirWoman.y - RAD(180);
			break;
		}
	}
}