#include "stdafx.h"
#include "Cube.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Cube::Cube()
		{
		}


		Cube::~Cube()
		{
		}

		HRESULT Cube::Setup(LPDIRECT3DTEXTURE9 t)
		{
			_texture = t;
			t->AddRef();

			//8개의 정점
			D3DXVECTOR3 cubes[8];
			int face[6][4];
			D3DXVECTOR2 tex[4] = { { 0, 1 }, { 0, 0 }, { 1, 0 }, { 1, 1 } };
			int index[6] = { 0, 1, 2, 0, 2, 3 };

			cubes[0] = D3DXVECTOR3(-1, -1, -1);
			cubes[1] = D3DXVECTOR3(-1, 1, -1);
			cubes[2] = D3DXVECTOR3(1, 1, -1);
			cubes[3] = D3DXVECTOR3(1, -1, -1);
			cubes[4] = D3DXVECTOR3(-1, -1, 1);
			cubes[5] = D3DXVECTOR3(-1, 1, 1);
			cubes[6] = D3DXVECTOR3(1, 1, 1);
			cubes[7] = D3DXVECTOR3(1, -1, 1);

			face[0][0] = 0;
			face[0][1] = 1;
			face[0][2] = 2;
			face[0][3] = 3;

			face[1][0] = 7;
			face[1][1] = 6;
			face[1][2] = 5;
			face[1][3] = 4;

			face[2][0] = 3;
			face[2][1] = 2;
			face[2][2] = 6;
			face[2][3] = 7;

			face[3][0] = 4;
			face[3][1] = 5;
			face[3][2] = 1;
			face[3][3] = 0;

			face[4][0] = 1;
			face[4][1] = 5;
			face[4][2] = 6;
			face[4][3] = 2;

			face[5][0] = 7;
			face[5][1] = 3;
			face[5][2] = 0;
			face[5][3] = 4;

			for (int i = 0; i < 6; ++i)
			{
				for (int j = 0; j < 6; ++j)
				{
					_vertex[i * 6 + j].p = cubes[face[i][index[j]]];
					_vertex[i * 6 + j].t = tex[index[j]];
				}
			}

			return S_OK;
		}

		void Cube::Release()
		{
			_texture->Release();
		}

		void Cube::Update()
		{
			D3DXMATRIXA16 rot;

			D3DXMatrixRotationY(&rot, RAD((GetTickCount() / 10) % 360));

			this->SetRotateLocal(rot);
		}

		void Cube::Render()
		{
			DEVICE->SetTransform(D3DTS_WORLD, &this->GetFinalMatrix());

			DEVICE->SetTexture(0, _texture);
			DEVICE->SetFVF(PNT_VERTEX::FVF);
			DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, _vertex, sizeof(PNT_VERTEX));
		}
	}
}