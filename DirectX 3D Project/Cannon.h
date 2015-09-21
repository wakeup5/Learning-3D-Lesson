#pragma once
#include "Transform.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		namespace Cannons
		{
			
			class CannonCube //ť�� ����
			{
			public:
				CannonCube()
					: _parent(NULL)
					, _vb(NULL)
					, _ib(NULL)
					, _pos(0, 0, 0)
					, _rot(0, 0, 0)
					, _scale(1, 1, 1)
					, _look(0, 0, 0)
					, _direction(0, 0, 1)
				{
				}
				virtual ~CannonCube() {}

				//ũ�Ⱑ 1, -0.5 ~ 0.5 ��ǥ ������ ť�갡 �������.
				//verScale : ���ؽ� ��ǥ ��ü ������
				//verRot : ���ؽ� ��ǥ ��ü ȸ��
				//verPos : ���ؽ� ��ǥ ��ü �̵�
				void Setup(
					D3DXVECTOR3 verScale = D3DXVECTOR3(1, 1, 1),//verScale : ���ؽ� ��ǥ ��ü ������
					D3DXVECTOR3 verRot = D3DXVECTOR3(0, 0, 0),//verRot : ���ؽ� ��ǥ ��ü ȸ��
					D3DXVECTOR3 verPos = D3DXVECTOR3(0, 0, 0));//verPos : ���ؽ� ��ǥ ��ü �̵�
				void Release();
				void Update();
				void Render(LPD3DXEFFECT pEffect);

				void SetPosition(float x, float y, float z);
				D3DXVECTOR3 GetPosition();
				void SetRotation(float x, float y, float z);
				D3DXVECTOR3 GetRotation();
				void SetScale(float x, float y, float z);
				D3DXVECTOR3 GetScale();

				D3DXMATRIXA16 GetLocalMatrix();
				D3DXMATRIXA16 GetPosMatrix() { return _matPos; }
				D3DXMATRIXA16 GetRotMatrix() { return _matRot; }
				D3DXMATRIXA16 GetScaleMatrix() { return _matScale; }

				void Look(D3DXVECTOR3 l) { _look = l; }

				void SetParent(CannonCube* p) { _parent = p; }
			protected:
				LPDIRECT3DVERTEXBUFFER9 _vb;
				LPDIRECT3DINDEXBUFFER9 _ib;

				D3DXVECTOR3 _pos;
				D3DXVECTOR3 _rot;
				D3DXVECTOR3 _scale;

				D3DXVECTOR3 _direction;

				D3DXVECTOR3 _look;

				D3DXMATRIXA16 _matPos, _matRot, _matScale, _matLocal;
				D3DXMATRIXA16 _rolling;

				CannonCube* _parent;

			};
			class Cannon : public CannonCube
			{
			private:
				CannonCube* _big;
				CannonCube* _small;

				float _fireTime = 0;
				//float _s
			public:
				Cannon();
				virtual ~Cannon();

				void Setup();//verPos : ���ؽ� ��ǥ ��ü �̵�
				void Release();
				void Update();
				void Render(LPD3DXEFFECT pEffect);

				void Look(D3DXVECTOR3 &look);

				bool IsReadyFire()
				{
					if (_fireTime + Util::RandomFloatRange(0.4, 0.8) < TIME_MGR->GetLastTime())
					{
						_fireTime = TIME_MGR->GetLastTime();
						return true;
					}

					return false;					
				}
			};
			static DWORD _sLightNum = 120;
			class CannonBullet : public CannonCube// //�Ƕ�̵� ����
			{
			private:
				DWORD _pLightNum;
				D3DLIGHT9 _light;
				D3DXVECTOR3 _vellocity;

				float _startTime;
			public:
				//static DWORD _sLightNum;
				bool _isDead = false;

				virtual void Update()
				{
					CannonCube::Update();

					_vellocity.y -= 2 * TIME_MGR->GetFrameDeltaSec();
					_pos += _vellocity * TIME_MGR->GetFrameDeltaSec();

					if (_pos.y < 0) _isDead = true;

					if (_startTime + 5 < TIME_MGR->GetLastTime()) _isDead = true;

					_light.Position = _pos;
					DEVICE->SetLight((DWORD)_pLightNum, &_light);	//����Ʈ ����̽��� ����
					DEVICE->LightEnable((DWORD)_pLightNum, true);

					SetRotation(RAD((GetTickCount() / 3) % 360), RAD((GetTickCount() / 3) % 360), RAD((GetTickCount() / 3) % 360));
				}

				virtual void Setup(
					D3DXVECTOR3 verScale = D3DXVECTOR3(1, 1, 1),//verScale : ���ؽ� ��ǥ ��ü ������
					D3DXVECTOR3 verRot = D3DXVECTOR3(0, 0, 0),//verRot : ���ؽ� ��ǥ ��ü ȸ��
					D3DXVECTOR3 verPos = D3DXVECTOR3(0, 0, 0))//verPos : ���ؽ� ��ǥ ��ü �̵�
				{
					CannonCube::Setup(verScale, verRot, verPos);

					_pLightNum = _sLightNum++;

					ZeroMemory(&_light, sizeof(D3DLIGHT9));	//�ʱ�ȭ
					_light.Type = D3DLIGHT_POINT;		//����Ʈ Ÿ��
					_light.Ambient = D3DXCOLOR(1, 1, 0.2, 1); //���� �÷��� ����
					_light.Diffuse = D3DXCOLOR(1, 1, 0.2, 1); //��ǻ�� �� (�ؽ��� ����)
					_light.Specular = D3DXCOLOR(1, 1, 0.2, 1);// ���� ���̴� ��. ���ݻ�. ���� ��½
					_light.Direction = D3DXVECTOR3(0, -1.0f, 0);
					_light.Position = _pos;
					//_light.Position.y += 2;
					_light.Range = 3;
					DEVICE->SetLight((DWORD)_pLightNum, &_light);	//����Ʈ ����̽��� ����
					DEVICE->LightEnable((DWORD)_pLightNum, true);		//����Ʈon,off �տ� ���ڴ� ����Ʈ�迭 �̶�� ���� �ɵ�.

					_startTime = TIME_MGR->GetLastTime();
				}

				virtual void SetVellocity(D3DXVECTOR3 direction, float power)
				{
					D3DXVec3Normalize(&_vellocity, &direction);
					_vellocity *= power;
				}

				virtual void Release()
				{
					DEVICE->LightEnable((DWORD)_pLightNum, false);

					CannonCube::Release();
				}
			};
		}
	}
}
