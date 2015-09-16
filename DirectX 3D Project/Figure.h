#pragma once
#include "Transform.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Figure :
			public Transform
		{
		protected:
			LPDIRECT3DTEXTURE9 _texture;
			PNT_VERTEX* _vertex;
			int _size;

			void initFigure(int size);
		public:
			Figure();
			virtual ~Figure();

			virtual HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			virtual void Release();
			virtual void Update();
			virtual void Render();
		};
	}
}