#include "stdafx.h"
#include "UITextBox.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		UITextBox::UITextBox()
			: _text("")
			, _fontFormat(DT_LEFT | DT_TOP | DT_WORDBREAK)
			, _color(0xffffffff)
		{
		}


		UITextBox::~UITextBox()
		{
		}

		void UITextBox::Setup()
		{

		}
		//virtual void Release();
		void UITextBox::Update()
		{
			UIWindow::Update();
		}
		void UITextBox::Render(LPD3DXSPRITE sprite)
		{
			UIWindow::Render(sprite);

			POINT pos = GetFinalPosition();
			RECT rc;
			rc.left = pos.x;
			rc.top = pos.y;
			rc.right = pos.x + _size.width;
			rc.bottom = pos.y + _size.height;

			LPD3DXFONT font = DXFONT_MGR->GetStyle("");

			font->DrawText(NULL, _text, strlen(_text), &rc, _fontFormat, _color);

			//DXFONT_MGR->PrintText(_text, rc, 0xffffffff);
		}
	}
}