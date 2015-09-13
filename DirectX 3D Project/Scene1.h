#pragma once
#include "Scene.h"

namespace NS_ROOT
{
	namespace NS_BASE
	{
		class Scene1 :
			public Scene
		{
		private:

			PC_VERTEX _vertex[6];

			NS_OBJECTS::Camera* _camera;

		public:
			Scene1();
			~Scene1();

			virtual HRESULT Setup();
			virtual void Release();
			virtual void Update(float timeDelta);
			virtual void Render();

			virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		};
	}
}
