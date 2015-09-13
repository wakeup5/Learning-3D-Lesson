#pragma once

namespace NS_ROOT
{
	namespace NS_BASE
	{
		class GameMain
		{
		private:
			Scene* _scene;
		public:
			GameMain();
			virtual ~GameMain();

			HRESULT Setup();
			void Release();
			void Update();
			void Render();

			LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
		};
	}//end NS_BASE
}//end NS_ROOT
