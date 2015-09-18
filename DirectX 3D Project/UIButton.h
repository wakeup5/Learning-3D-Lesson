#pragma once
#include "UITextBox.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		class UIButton : public UITextBox
		{
		private:
			LPDIRECT3DTEXTURE9 _overT, _normalT, _clickT;
			D3DXIMAGE_INFO _overI, _normalI, _clickI;
		public:
			UIButton();
			virtual ~UIButton();

			virtual void Setup();
			//virtual void Release();
			virtual void Update();
			virtual void Render(LPD3DXSPRITE sprite);

			void SetButtonTexture(char* normal, char* over, char* click);
		};
	}
}