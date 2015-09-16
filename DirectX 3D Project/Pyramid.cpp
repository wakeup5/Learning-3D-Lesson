#include "stdafx.h"
#include "Pyramid.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Pyramid::Pyramid()
		{
		}


		Pyramid::~Pyramid()
		{
		}

		HRESULT Pyramid::Setup(LPDIRECT3DTEXTURE9 t)
		{
			FigureC::Setup(t);
			initFigure(18);

			_color = NS_UTIL::RandomIntRange(0, 0xffffffff);

			//8개의 정점
			D3DXVECTOR3 v[5];

			v[0] = D3DXVECTOR3(0, 0, 0);
			v[1] = D3DXVECTOR3(-1, -1, -1);
			v[2] = D3DXVECTOR3(1, -1, -1);
			v[3] = D3DXVECTOR3(1, 1, -1);
			v[4] = D3DXVECTOR3(-1, 1, -1);

			_vertex[0] = PC_VERTEX(v[0], _color);
			_vertex[1] = PC_VERTEX(v[1], _color);
			_vertex[2] = PC_VERTEX(v[2], _color);

			_vertex[3] = PC_VERTEX(v[0], _color);
			_vertex[4] = PC_VERTEX(v[2], _color);
			_vertex[5] = PC_VERTEX(v[3], _color);

			_vertex[6] = PC_VERTEX(v[0], _color);
			_vertex[7] = PC_VERTEX(v[3], _color);
			_vertex[8] = PC_VERTEX(v[4], _color);

			_vertex[9] = PC_VERTEX(v[0], _color);
			_vertex[10] = PC_VERTEX(v[4], _color);
			_vertex[11] = PC_VERTEX(v[1], _color);

			_vertex[12] = PC_VERTEX(v[1], _color);
			_vertex[13] = PC_VERTEX(v[4], _color);
			_vertex[14] = PC_VERTEX(v[3], _color);

			_vertex[15] = PC_VERTEX(v[1], _color);
			_vertex[16] = PC_VERTEX(v[3], _color);
			_vertex[17] = PC_VERTEX(v[2], _color);

			_startTime = GetTickCount();
			return S_OK;
		}

		void Pyramid::Release()
		{
			FigureC::Release();
		}

		void Pyramid::Update()
		{
			SetRotateLocal(0, angleY, RAD((GetTickCount() / 3 % 360)));

			D3DXMATRIXA16 rotMat;
			D3DXMatrixRotationY(&rotMat, angleY);
		
			D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
			D3DXVec3TransformNormal(&direction, &direction, &rotMat);

			SetWorldPosition(GetWorldPosition() + (direction / 2));

			SetScale(0.2f, 0.2f, 1.2f);

			if (GetTickCount() - _startTime > 2000)
			{
				_b = true;
			}
		}

		void Pyramid::Render()
		{
			FigureC::Render();
		}
	}
}