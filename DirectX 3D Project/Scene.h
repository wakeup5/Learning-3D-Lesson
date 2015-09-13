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

			virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;
		};
	}
}

