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

		HRESULT Cube::Setup()
		{
			//8개의 정점
			PC_VERTEX cubes[8];
			int face[6][4];
			int index[6] = { 0, 1, 2, 0, 2, 3 };

			cubes[0] = PC_VERTEX(-1, -1, -1, 0xffff0000);
			cubes[1] = PC_VERTEX(-1, 1, -1, 0xff00ff00);
			cubes[2] = PC_VERTEX(1, 1, -1, 0xff0000ff);
			cubes[3] = PC_VERTEX(1, -1, -1, 0xff880000);
			cubes[4] = PC_VERTEX(-1, -1, 1, 0xff008800);
			cubes[5] = PC_VERTEX(-1, 1, 1, 0xff000088);
			cubes[6] = PC_VERTEX(1, 1, 1, 0xffffff00);
			cubes[7] = PC_VERTEX(1, -1, 1, 0xffff00ff);

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
					_vertex[i * 6 + j] = cubes[face[i][index[j]]];
				}
			}

			return S_OK;
		}

		void Cube::Release()
		{

		}

		void Cube::Update()
		{

		}

		void Cube::Render()
		{
			DEVICE->SetTransform(D3DTS_WORLD, &this->GetFinalMatrix());
			DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, _vertex, sizeof(PC_VERTEX));
		}
	}
}