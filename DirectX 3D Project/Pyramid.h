#pragma once
#include "Figure.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Pyramid : public Figure
		{
		public:
			Pyramid();
			virtual ~Pyramid();

			HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			void Release();
			void Update();
			void Render();
		};
	}
}