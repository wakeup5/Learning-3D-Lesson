#pragma once
#include "Figure.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Pyramid : public FigureC
		{
		private:
			DWORD _color = 0xffffffff;
			DWORD _startTime;
		public:
			Pyramid();
			virtual ~Pyramid();

			HRESULT Setup(LPDIRECT3DTEXTURE9 t = NULL);
			void Release();
			void Update();
			void Render();

			inline void SetColor(DWORD c) { _color = c; }

			float angleY = 0;
			bool _b = false;
		};
	}
}