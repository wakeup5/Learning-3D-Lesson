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
	_cube->Scaling(0.2, 0.2, 0.2);
	_cube->SetWorldPosition(0, 5, 0);
	
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	D3DLIGHT9 stLight;							//����
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));	//�ʱ�ȭ
	stLight.Type = D3DLIGHT_DIRECTIONAL;		//����Ʈ Ÿ��
	stLight.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0); //���� �÷��� ����
	stLight.Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0); //��ǻ�� �� (�ؽ��� ����)
	stLight.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0);// ���� ���̴� ��. ���ݻ�. ���� ��½
	D3DXVECTOR3 vDir(0, -1.0f, 0);  //���� �����ش� ����
	D3DXVec3Normalize(&vDir, &vDir);	//�븻������ ��������. �ε��Ҽ��� �������� ���� �� �־� �� ��꿡 ���� �� �� ���� �ִ�.
	stLight.Direction = vDir;
	DEVICE->SetLight(0, &stLight);	//����Ʈ ����̽��� ����
	DEVICE->LightEnable(0, true);		//����Ʈon,off �տ� ���ڴ� ����Ʈ�迭 �̶�� ���� �ɵ�.

	return S_OK;
}

void Scene_15_09_18_2::Release()
{
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(_c[i]);
	}

	_cube->Release();
	delete _cube;
}

void Scene_15_09_18_2::Update(float timedelta)
{
	D3DXVECTOR3 pos = _cube->GetWorldPosition();
	pos.x /= 2;
	pos.z /= 2;

	_cam->SetWorldPosition(pos + D3DXVECTOR3(0, 20, 0));
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

		if (D3DXVec3Length(&(_cube->GetWorldPosition() - _c[i]->GetPosition())) < 12)
			_c[i]->Look(_cube->GetWorldPosition());
		else
			_c[i]->Look(_c[i]->GetPosition() + D3DXVECTOR3(0, 5, -10));
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
}

void Scene_15_09_18_2::Render()
{
	//GIZMO_MGR->WorldGrid(1, 10);
	_cube->Render();
	for (int i = 0; i < 10; i++)
	{
		_c[i]->Render();
		//_c[i]->Look(_cube->GetWorldPosition());
	}
}
