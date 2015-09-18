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
			Figure::Setup(t);
			initFigure(36);

			//8개의 정점
			D3DXVECTOR3 cubes[8];
			int face[6][4];
			D3DXVECTOR2 tex[4] = { { 0, 1 }, { 0, 0 }, { 1, 0 }, { 1, 1 } };
			int index[6] = { 0, 1, 2, 0, 2, 3 };

			cubes[0] = D3DXVECTOR3(-1, -2, -1);
			cubes[1] = D3DXVECTOR3(-1, 0, -1);
			cubes[2] = D3DXVECTOR3(1, 0, -1);
			cubes[3] = D3DXVECTOR3(1, -2, -1);
			cubes[4] = D3DXVECTOR3(-1, -2, 1);
			cubes[5] = D3DXVECTOR3(-1, 0, 1);
			cubes[6] = D3DXVECTOR3(1, 0, 1);
			cubes[7] = D3DXVECTOR3(1, -2, 1);

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

			PNT_VERTEX temp;

			for (int i = 0; i < 6; ++i)
			{
				D3DXVECTOR3 normal;

				D3DXVec3Cross(&normal, &(cubes[face[i][1]] - cubes[face[i][0]]), &(cubes[face[i][2]] - cubes[face[i][0]]));
				D3DXVec3Normalize(&normal, &normal);

				for (int j = 0; j < 6; ++j)
				{
					temp = PNT_VERTEX(cubes[face[i][index[j]]], normal, tex[index[j]]);
					//_vertex[i * 6 + j].p = 
					//_vertex[i * 6 + j].t = tex[index[j]];
					//_vertex[i * 6 + j].n = normal;
					_vertex.push_back(temp);
				}
			}

			SetBuffer();

			return S_OK;
		}

		void Cube::Release()
		{
			Figure::Release();
		}

		void Cube::Update()
		{
			
		}

		void Cube::Render()
		{
			Figure::Render();
		}
		void Cube::SetScale(float x, float y, float z)
		{
			D3DXMATRIXA16 mat;

			D3DXMatrixScaling(&mat, x, y, z);
			for (int i = 0; i < _size; i++)
			{
				D3DXVec3TransformNormal(&_vertex[i].p, &_vertex[i].p, &mat);
			}
		}
	}
}