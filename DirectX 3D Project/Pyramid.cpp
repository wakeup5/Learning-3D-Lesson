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
			Figure::Setup(t);
			initFigure(18);

			//8개의 정점
			D3DXVECTOR3 v[5];
			
			v[0] = D3DXVECTOR3(0, 0, 0);
			v[1] = D3DXVECTOR3(-1, -1, -1);
			v[2] = D3DXVECTOR3(-1, 1, -1);
			v[3] = D3DXVECTOR3(1, 1, -1);
			v[4] = D3DXVECTOR3(1, -1, -1);

			_vertex[0].p = v[0];
			_vertex[1].p = v[1];
			_vertex[2].p = v[2];

			_vertex[3].p = v[0];
			_vertex[4].p = v[2];
			_vertex[5].p = v[3];

			_vertex[6].p = v[0];
			_vertex[7].p = v[3];
			_vertex[8].p = v[4];

			_vertex[9].p = v[0];
			_vertex[10].p = v[4];
			_vertex[11].p = v[1];

			_vertex[12].p = v[1];
			_vertex[13].p = v[2];
			_vertex[14].p = v[3];

			_vertex[15].p = v[1];
			_vertex[16].p = v[3];
			_vertex[17].p = v[4];

			return S_OK;
		}

		void Pyramid::Release()
		{
			Figure::Release();
		}

		void Pyramid::Update()
		{
			
		}

		void Pyramid::Render()
		{
			Figure::Render();
		}
	}
}