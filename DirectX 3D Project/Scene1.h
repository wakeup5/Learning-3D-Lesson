#pragma once
#include "Scene.h"
#include "Cube.h"

namespace NS_ROOT
{
	namespace NS_BASE
	{
		//class Cube;

		class Scene1 : public Scene
		{
		private:

			PC_VERTEX _vertex[6];

			NS_OBJECTS::Camera* _camera;

			NS_OBJECTS::Cube* _cube;

		public:
			Scene1();
			~Scene1();

			virtual HRESULT Setup();
			virtual void Release();
			virtual void Update(float timeDelta);
			virtual void Render();
		};
	}
}
