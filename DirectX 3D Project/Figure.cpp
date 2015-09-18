#include "stdafx.h"
#include "Figure.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Figure::Figure()
			: _vertexBuffer(NULL)
		{
		}


		Figure::~Figure()
		{
		
		}

		void Figure::initFigure(int size)
		{
			_size = size;
			
			//_vertex = new PNT_VERTEX[_size];
		}

		HRESULT Figure::Setup(LPDIRECT3DTEXTURE9 t)
		{
			_texture = t;

			if (_texture) _texture->AddRef();

			return S_OK;
		}

		void Figure::Release()
		{
			if (_texture) _texture->Release();
		}
		void Figure::Update()
		{

		}
		void Figure::Render()
		{
			DEVICE->SetStreamSource(0, _vertexBuffer, 0, sizeof(PNT_VERTEX));
			DEVICE->SetTransform(D3DTS_WORLD, &this->GetFinalMatrix());

			if (_texture)
				DEVICE->SetTexture(0, _texture);

			DEVICE->SetFVF(PNT_VERTEX::FVF);
			//DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, _size / 3, &_vertex[0], sizeof(PNT_VERTEX));
			DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertex.size() / 3);
		}

		void Figure::SetBuffer()
		{
			DEVICE->CreateVertexBuffer(_vertex.size() * sizeof(PNT_VERTEX), 0, PNT_VERTEX::FVF, D3DPOOL_MANAGED, &_vertexBuffer, NULL);

			PNT_VERTEX* pv = NULL;

			_vertexBuffer->Lock(0, 0, (LPVOID*)&pv, 0);

			memcpy(pv, &_vertex[0], _vertex.size() * sizeof(PNT_VERTEX));

			_vertexBuffer->Unlock();
		}

		FigureC::FigureC()
		{
		}


		FigureC::~FigureC()
		{

		}

		void FigureC::initFigure(int size)
		{
			_size = size;

			_vertex = new PC_VERTEX[_size];
		}

		HRESULT FigureC::Setup(LPDIRECT3DTEXTURE9 t)
		{
			_texture = t;

			if (_texture) _texture->AddRef();

			return S_OK;
		}

		void FigureC::Release()
		{
			if (_texture) _texture->Release();
		}
		void FigureC::Update()
		{

		}
		void FigureC::Render()
		{
			DEVICE->SetTransform(D3DTS_WORLD, &this->GetFinalMatrix());

			if (_texture)
				DEVICE->SetTexture(0, _texture);

			DEVICE->SetFVF(PC_VERTEX::FVF);
			DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, _size / 3, _vertex, sizeof(PC_VERTEX));
		}
	}
}