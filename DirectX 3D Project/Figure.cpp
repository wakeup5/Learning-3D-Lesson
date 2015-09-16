#include "stdafx.h"
#include "Figure.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Figure::Figure()
		{
		}


		Figure::~Figure()
		{
		
		}

		void Figure::initFigure(int size)
		{
			_size = size;
			
			_vertex = new PNT_VERTEX[_size];
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
			DEVICE->SetTransform(D3DTS_WORLD, &this->GetFinalMatrix());

			if (_texture)
				DEVICE->SetTexture(0, _texture);

			DEVICE->SetFVF(PNT_VERTEX::FVF);
			DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, _size / 3, _vertex, sizeof(PNT_VERTEX));
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