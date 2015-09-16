#pragma once

namespace NS_ROOT
{
	namespace NS_BASE
	{
		class Scene
		{
		public:
			Scene() {}
			virtual ~Scene() {}

			virtual HRESULT Setup() = 0;
			virtual void Release() = 0;
			virtual void Update(float timeDelta) = 0;
			virtual void Render() = 0;

			virtual inline LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
			{
				if (iMessage == WM_KEYDOWN && wParam == VK_ESCAPE) PostQuitMessage(0);

				return DefWindowProc(hWnd, iMessage, wParam, lParam);
			}
		};

		/*
		LRESULT CALLBACK Scene::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
		{
			return DefWindowProc(hWnd, iMessage, wParam, lParam);
		}
		*/
	}
}

