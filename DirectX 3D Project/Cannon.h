#pragma once
#include "Transform.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		namespace Cannons
		{
			
			class CannonCube //큐브 형태
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

				//크기가 1, -0.5 ~ 0.5 좌표 사이의 큐브가 만들어짐.
				//verScale : 버텍스 좌표 자체 사이즈
				//verRot : 버텍스 좌표 자체 회전
				//verPos : 버텍스 좌표 자체 이동
				void Setup(
					D3DXVECTOR3 verScale = D3DXVECTOR3(1, 1, 1),//verScale : 버텍스 좌표 자체 사이즈
					D3DXVECTOR3 verRot = D3DXVECTOR3(0, 0, 0),//verRot : 버텍스 좌표 자체 회전
					D3DXVECTOR3 verPos = D3DXVECTOR3(0, 0, 0));//verPos : 버텍스 좌표 자체 이동
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

				void Setup();//verPos : 버텍스 좌표 자체 이동
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
			class CannonBullet : public CannonCube// //피라미드 형태
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
					DEVICE->SetLight((DWORD)_pLightNum, &_light);	//라이트 디바이스에 셋팅
					DEVICE->LightEnable((DWORD)_pLightNum, true);

					SetRotation(RAD((GetTickCount() / 3) % 360), RAD((GetTickCount() / 3) % 360), RAD((GetTickCount() / 3) % 360));
				}

				virtual void Setup(
					D3DXVECTOR3 verScale = D3DXVECTOR3(1, 1, 1),//verScale : 버텍스 좌표 자체 사이즈
					D3DXVECTOR3 verRot = D3DXVECTOR3(0, 0, 0),//verRot : 버텍스 좌표 자체 회전
					D3DXVECTOR3 verPos = D3DXVECTOR3(0, 0, 0))//verPos : 버텍스 좌표 자체 이동
				{
					CannonCube::Setup(verScale, verRot, verPos);

					_pLightNum = _sLightNum++;

					ZeroMemory(&_light, sizeof(D3DLIGHT9));	//초기화
					_light.Type = D3DLIGHT_POINT;		//라이트 타입
					_light.Ambient = D3DXCOLOR(1, 1, 0.2, 1); //광원 컬러값 설정
					_light.Diffuse = D3DXCOLOR(1, 1, 0.2, 1); //디퓨즈 값 (텍스쳐 원색)
					_light.Specular = D3DXCOLOR(1, 1, 0.2, 1);// 빛이 모이는 곳. 정반사. 스뎅 번쩍
					_light.Direction = D3DXVECTOR3(0, -1.0f, 0);
					_light.Position = _pos;
					//_light.Position.y += 2;
					_light.Range = 3;
					DEVICE->SetLight((DWORD)_pLightNum, &_light);	//라이트 디바이스에 셋팅
					DEVICE->LightEnable((DWORD)_pLightNum, true);		//라이트on,off 앞에 숫자는 라이트배열 이라고 보면 될듯.

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
