#include "stdafx.h"
#include "UIButton.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		UIButton::UIButton()
			: _clickT(NULL)
			, _overT(NULL)
			, _normalT(NULL)
		{
		}


		UIButton::~UIButton()
		{
		}

		void UIButton::Setup()
		{
			UITextBox::Setup();
		}
		void UIButton::Update()
		{
			UITextBox::Update();

			if (_isMouseClick)
			{
				if(_clickT) SetBackground(_clickT, _clickI);
			}
			else if (_isMouseOver)
			{
				if (_overT) SetBackground(_overT, _overI);
			}
			else
			{
				if (_normalT) SetBackground(_normalT, _normalI);
			}
		}
		void UIButton::Render(LPD3DXSPRITE sprite)
		{
			UITextBox::Render(sprite);
		}

		void UIButton::SetButtonTexture(char* normal, char* over, char* click)
		{
			_normalT = TEXTURE_MGR->GetTexture(normal, &_normalI);
			_overT = TEXTURE_MGR->GetTexture(over, &_overI);
			_clickT = TEXTURE_MGR->GetTexture(click, &_clickI);
		}
	}
}