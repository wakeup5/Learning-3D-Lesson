#include "stdafx.h"
#include "Scene_15_09_18_2.h"


Scene_15_09_18_2::Scene_15_09_18_2()
{

}


Scene_15_09_18_2::~Scene_15_09_18_2()
{

}

HRESULT Scene_15_09_18_2::Setup()
{
	for (int i = 0; i < 10; i++)
	{
		_c[i] = new Cannon;
		_c[i]->Setup();
		_c[i]->SetPosition(
			RandomFloatRange(-10, 10),
			0,
			-20 + i * 4);
	}

	_cam = new Camera;

	_cube = new Cube;
	_cube->Setup();
	_cube->Scaling(-0.8, -0.9, -0.6);
	_cube->SetWorldPosition(0, 13, 0);
	
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	float lightPower = 0.7f;
	D3DLIGHT9 stLight;							//선언
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));	//초기화
	stLight.Type = D3DLIGHT_DIRECTIONAL;		//라이트 타입
	stLight.Ambient = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower); //광원 컬러값 설정
	stLight.Diffuse = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower); //디퓨즈 값 (텍스쳐 원색)
	stLight.Specular = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower);// 빛이 모이는 곳. 정반사. 스뎅 번쩍
	D3DXVECTOR3 vDir(0, -1.0f, 0);  //빛이 내려쬐는 방향
	D3DXVec3Normalize(&vDir, &vDir);	//노말라이즈 시켜주자. 부동소수점 오차값이 있을 수 있어 빛 계산에 오류 가 날 수도 있다.
	stLight.Direction = vDir;
	DEVICE->SetLight(0, &stLight);	//라이트 디바이스에 셋팅
	DEVICE->LightEnable(0, true);		//라이트on,off 앞에 숫자는 라이트배열 이라고 보면 될듯.

	//_b = new CannonBullet;
	//_b->Setup();
	//_b->SetVellocity(D3DXVECTOR3(0, 1, 1), 5);

	//셰이더 설정
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlag = 0;
#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;
#endif
	D3DXCreateEffectFromFile(DEVICE, "BlinnPhong.fx", NULL, NULL, dwShaderFlag, NULL, &pEffect, &pError);

	return S_OK;
}

void Scene_15_09_18_2::Release()
{
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(_c[i]);
	}
	
	for (int i = 0; i < _b.size(); i++)
	{
		_b[i].Release();
	}
	_b.clear();

	_cube->Release();
	delete _cube;
}

void Scene_15_09_18_2::Update(float timedelta)
{
	D3DXVECTOR3 pos = _cube->GetWorldPosition();
	pos.x /= 2;
	pos.z /= 2;

	_cam->SetWorldPosition(pos + D3DXVECTOR3(0, 10, 0));
	_cam->LookPosition(pos + D3DXVECTOR3(0, 0, 1));
	//_cam->SetRotateLocal(RAD(90), 0, 0);
	_cam->UpdateCamToDevice(DEVICE);

	//_cam->DefaultControl(timedelta);

	//LOG_MGR->AddLog("%f, %f, %f", _cam->GetWorldPosition().x, _cam->GetWorldPosition().y, _cam->GetWorldPosition().z);
	
	_cube->Update();
	D3DXVECTOR3 temp;
	for (int i = 0; i < 10; i++)
	{
		temp = _c[i]->GetPosition();
		temp.z -= 5 * timedelta;

		if (temp.z < -20)
		{
			temp.x = RandomFloatRange(-10, 10);
			temp.y = 0;
			temp.z = 20;
		}
		_c[i]->SetPosition(temp.x, temp.y, temp.z);

		_c[i]->Update();

		if (D3DXVec3Length(&(_cube->GetWorldPosition() - _c[i]->GetPosition())) < 20)
		{
			_c[i]->Look(_cube->GetWorldPosition());

			if (Util::RandomIntRange(0, 100) < 2 )
			{
				CannonBullet b;
				b.Setup();
				b.SetPosition(temp.x, temp.y, temp.z);
				b.SetVellocity(_cube->GetWorldPosition() - _c[i]->GetPosition(), 20);
				_b.push_back(b);
			}
		}
		else
		{
			_c[i]->Look(_c[i]->GetPosition() + D3DXVECTOR3(0, 5, -10));
		}
			//_c[i]->Look(D3DXVECTOR3(0, 0, 0));
	}


	if (KEY_MGR->IsStayDown('W'))
	{
		_cube->MovePositionSelf(0, 0, 0.1);
	}
	if (KEY_MGR->IsStayDown('S'))
	{
		_cube->MovePositionSelf(0, 0, -0.1);
	}
	if (KEY_MGR->IsStayDown('A'))
	{
		_cube->MovePositionSelf(-0.1, 0, 0);
	}
	if (KEY_MGR->IsStayDown('D'))
	{
		_cube->MovePositionSelf(0.1, 0, 0);
	}

	for (int i = 0; i < _b.size(); i++)
	{
		_b[i].Update();

		if (_b[i]._isDead)
		{
			_b[i].Release();
			
			_b.erase(_b.begin() + i);
			i--;
		}
	}
	DEVICE->LightEnable(0, true);
}

void Scene_15_09_18_2::Render()
{
	//GIZMO_MGR->WorldGrid(1, 10);

	_cube->Render();

	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProjection);

	this->pEffect->SetMatrix("matView", &matView);
	this->pEffect->SetMatrix("matProjection", &matProjection);

	D3DXVECTOR4 vMaterialDiffuseColor(0.8, 0.7, 1, 1);
	this->pEffect->SetVector("vMaterialDiffuseColor", &vMaterialDiffuseColor);
	D3DXVECTOR4 vMaterialSpecularColor(0.8, 0.8, 0.8, 1);
	this->pEffect->SetVector("vMaterialSpecularColor", &vMaterialSpecularColor);

	this->pEffect->SetFloat("fPower", 30.0f);

	D3DXVECTOR4 lightDir(0, -1, 0, 1);
	this->pEffect->SetVector("vLightDir", &lightDir);

	D3DXVECTOR4 eyePos(0, 30, 0, 1);
	this->pEffect->SetVector("vEyePos", &eyePos);

	this->pEffect->SetTechnique("MyShader");

	for (int i = 0; i < 10; i++)
	{
		_c[i]->Render(pEffect);
		//_c[i]->Look(_cube->GetWorldPosition());
	}

	for (int i = 0; i < _b.size(); i++)
	{
		//if (_b[i] == NULL) continue;

		_b[i].Render(NULL);
	}
}
