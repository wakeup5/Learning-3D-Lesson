#pragma once
#include "Figure.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Cube : public Figure
		{
		public:
			Cube();
			virtual ~Cube();

			HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			void Release();
			void Update();
			void Render();
		};
	}
}
