#pragma once
#include "Transform.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Cube : public Transform
		{
		private:
			LPDIRECT3DTEXTURE9 _texture;
			PNT_VERTEX _vertex[36];
		public:
			Cube();
			virtual ~Cube();

			HRESULT Setup(LPDIRECT3DTEXTURE9 t);
			void Release();
			void Update();
			void Render();
		};
	}
}
