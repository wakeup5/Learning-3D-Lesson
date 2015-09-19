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
	_c[0] = new Cannon;
	_c[0]->Setup();
	_c[0]->SetPosition(2, 0, 2);

	_c[1] = new Cannon;
	_c[1]->Setup();
	_c[1]->SetPosition(10, 0, 10);

	_c[2] = new Cannon;
	_c[2]->Setup();
	_c[2]->SetPosition(-4, 0, 5);

	_c[3] = new Cannon;
	_c[3]->Setup();
	_c[3]->SetPosition(9, 0, -7);

	_c[4] = new Cannon;
	_c[4]->Setup();
	_c[4]->SetPosition(-6, 0, -5);

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
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE(_c[i]);
	}

	_cube->Release();
	delete _cube;
}

void Scene_15_09_18_2::Update(float timedelta)
{
	_cam->SetWorldPosition(_cube->GetWorldPosition() + D3DXVECTOR3(0, 20, 0));
	_cam->LookPosition(_cube->GetWorldPosition() + D3DXVECTOR3(0, 0, 1));
	//_cam->SetRotateLocal(RAD(90), 0, 0);
	_cam->UpdateCamToDevice(DEVICE);

	//_cam->DefaultControl(timedelta);

	//LOG_MGR->AddLog("%f, %f, %f", _cam->GetWorldPosition().x, _cam->GetWorldPosition().y, _cam->GetWorldPosition().z);
	
	_cube->Update();

	for (int i = 0; i < 5; i++)
	{
		_c[i]->Update();
		_c[i]->Look(_cube->GetWorldPosition());
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
	for (int i = 0; i < 5; i++)
	{
		_c[i]->Render();
		//_c[i]->Look(_cube->GetWorldPosition());
	}
}
