#include "stdafx.h"
#include "UIWindow.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		UIWindow::UIWindow()
			: _root(this)
			, _position(0, 0, 0)
			, _size(0, 0)
			, _deligate(NULL)
			, _background(NULL)
		{
			
		}

		UIWindow::~UIWindow()
		{

		}

		void UIWindow::Setup()
		{

		}
		void UIWindow::Update()
		{

		}
		void UIWindow::Render(LPD3DXSPRITE sprite)
		{


			for (int i = 0; i < _childWindow.size(); ++i)
			{
				_childWindow[i]->Render(sprite);
			}
		}

		void UIWindow::AttachTo(UIWindow* parents)
		{
			parents->AddChild(this);
		}
		void UIWindow::AddChild(UIWindow* child)
		{
			this->_childWindow.push_back(child);
			child->_root = this->_root;
		}

		void UIWindow::SetPosition(float x, float y)
		{

		}
		void UIWindow::SetSize(int width, int height)
		{

		}

		void UIWindow::SetBackground()
		{

		}
	}
}