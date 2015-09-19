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

				void Setup();//verPos : ���ؽ� ��ǥ ��ü �̵�
				void Release();
				void Update();
				void Render();

				void Look(D3DXVECTOR3 &look);
			};

			class CannonBullet //�Ƕ�̵� ����
			{
			private:
				D3DLIGHT9 _light;

				D3DXVECTOR3 _direction;
			};
		}
	}
}
