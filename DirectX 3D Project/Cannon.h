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
				void Render();

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
			private:
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

			public:
				Cannon();
				virtual ~Cannon();

				void Setup();//verPos : 버텍스 좌표 자체 이동
				void Release();
				void Update();
				void Render();

				void Look(D3DXVECTOR3 &look);
			};

			class CannonBullet //피라미드 형태
			{
			private:
				D3DLIGHT9 _light;

				D3DXVECTOR3 _direction;
			};
		}
	}
}
