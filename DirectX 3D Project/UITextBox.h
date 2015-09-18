#pragma once
#include "UIWindow.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		class UITextBox :
			public UIWindow
		{
		private:
			char* _text;
			DWORD _fontFormat;
			D3DCOLOR _color;
		public:
			UITextBox();
			virtual ~UITextBox();

			virtual void Setup();
			//virtual void Release();
			virtual void Update();
			virtual void Render(LPD3DXSPRITE sprite);

			void SetText(char* t) { _text = t; }
			void SetFontFormat(DWORD format) { _fontFormat = format; }
			void SetColor(D3DCOLOR color) { _color = color; }
		};
	}
}
