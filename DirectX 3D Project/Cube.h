#pragma once
#include "Transform.h"
namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		class Cube : public Transform
		{
		private:
			PC_VERTEX _vertex[36];
		public:
			Cube();
			virtual ~Cube();

			HRESULT Setup();
			void Release();
			void Update();
			void Render();
		};
	}
}
