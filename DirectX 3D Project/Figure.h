#pragma once
#include "Transform.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Figure : public Transform
		{
		protected:
			LPDIRECT3DTEXTURE9 _texture;
			std::vector<PNT_VERTEX> _vertex;
			int _size;

			//vertex buffer
			LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;

			void initFigure(int size);
		public:
			Figure();
			virtual ~Figure();

			virtual HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			virtual void Release();
			virtual void Update();
			virtual void Render();

			void SetBuffer();
		};

		
		class FigureC : public Transform
		{
		protected:
			LPDIRECT3DTEXTURE9 _texture;
			PC_VERTEX* _vertex;
			int _size;

			void initFigure(int size);
			//void SetBuffer();
		public:
			FigureC();
			virtual ~FigureC();

			virtual HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			virtual void Release();
			virtual void Update();
			virtual void Render();
		};
	}
}