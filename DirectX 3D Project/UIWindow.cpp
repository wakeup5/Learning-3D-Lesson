#include "stdafx.h"
#include "UIWindow.h"

namespace NS_ROOT
{
	namespace NS_UI
	{
		UIWindow::UIWindow()
			: _root(this)
			, _parent(NULL)
			, _position(0, 0, 0)
			, _size(0, 0)
			, _deligate(NULL)
			, _texture(NULL)
			, _isHidden(false)
			, _isMouseOver(false)
			, _isMouseClick(false)
			, _tagNum(0)
		{
			D3DXMatrixIdentity(&_matSize);

#ifdef _DEBUG
			_isDrawBounding = true;
#else
			_isDrawBounding = false;
#endif
		}

		UIWindow::~UIWindow()
		{

		}

		void UIWindow::Setup()
		{

		}
		void UIWindow::Release()
		{
			for (int i = 0; i < _child.size(); ++i)
			{
				_child[i]->Release();
				SAFE_DELETE(_child[i]);
			}
			_texture->Release();
		}
		void UIWindow::Update()
		{
			for (int i = 0; i < _child.size(); ++i)
			{
				_child[i]->Update();
				if (_child[i]->IsThisMouseOver())
				{
					//LOG_MGR->AddLog("자식 들어왔니?");
					_isMouseClick = false;
					_isMouseOver = false;

					return;
				}
			}

			if (_isHidden)
				return;

			POINT pos = GetFinalPosition();

			RECT rc;
			SetRect(&rc, pos.x, pos.y, pos.x + _size.width, pos.y + _size.height);

			if (PtInRect(&rc, GS.mousePos))
			{
				if (!_isMouseOver)
				{
					if(_deligate) _deligate->OnMouseOver(this, this->_root);
					_isMouseOver = true;
				}
					

				if (GS.isMouseClick)
				{
					GS.isUIClick = true;
					if (!_isMouseClick)
					{
						if (_deligate) _deligate->OnClickDown(this, this->_root);
						_isMouseClick = true;
					}

					if (_deligate) _deligate->OnClick(this, this->_root);
				}
				else
				{
					if (_isMouseClick)
					{
						GS.isUIClick = false;
						if (_deligate) _deligate->OnClickUp(this, this->_root);
						_isMouseClick = false;
					}
				}
			}
			else
			{
				if (_isMouseOver)
				{
					if (_deligate) _deligate->OnMouseOut(this, this->_root);
					_isMouseOver = false;
				}
			}

			if (_isMouseClick)
			{
				if (_deligate) _deligate->OnDrag(this, this->_root);
			}
			
		}

		void UIWindow::Render(LPD3DXSPRITE sprite)
		{
			if (_isHidden)
				return;

			D3DXMATRIXA16 matPos, matTotal;

			//이동
			POINT pos = GetFinalPosition();

			D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.0f);

			//합
			D3DXMatrixIdentity(&matTotal);
			matTotal = _matSize * matPos;

			if (_texture)
			{
				sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

				sprite->SetTransform(&matTotal);

				RECT rc;
				SetRect(&rc, 0, 0, _textureInfo.Width, _textureInfo.Height);
				sprite->Draw(_texture,
					&rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					D3DCOLOR_ARGB(255, 255, 255, 255));

				//Sprite->Draw(buttonTexture, NULL, NULL, &D3DXVECTOR3(-width2, -height2, 0.0), whitecol);

				sprite->End();
			}

			if (_isDrawBounding)
			{
				std::vector<RHWC_VERTEX> vecVertex;
				vecVertex.reserve(5);

				RHWC_VERTEX v;

				v.c = D3DCOLOR_XRGB(255, 0, 0);
				v.p = D3DXVECTOR4(matTotal._41, matTotal._42, 0, 1);
				vecVertex.push_back(v);

				v.c = D3DCOLOR_XRGB(255, 0, 0);
				v.p = D3DXVECTOR4(matTotal._41 + _size.width, matTotal._42, 0, 1);
				vecVertex.push_back(v);

				v.c = D3DCOLOR_XRGB(255, 0, 0);
				v.p = D3DXVECTOR4(matTotal._41 + _size.width, matTotal._42 + _size.height, 0, 1);
				vecVertex.push_back(v);

				v.c = D3DCOLOR_XRGB(255, 0, 0);
				v.p = D3DXVECTOR4(matTotal._41, matTotal._42 + _size.height, 0, 1);
				vecVertex.push_back(v);

				v.c = D3DCOLOR_XRGB(255, 0, 0);
				v.p = D3DXVECTOR4(matTotal._41, matTotal._42, 0, 1);
				vecVertex.push_back(v);

				DEVICE->SetFVF(RHWC_VERTEX::FVF);
				DEVICE->DrawPrimitiveUP(
					D3DPT_LINESTRIP, 4, &vecVertex[0], sizeof(RHWC_VERTEX));
			}

			for (int i = 0; i < _child.size(); ++i)
			{
				_child[i]->Render(sprite);
			}
		}

		void UIWindow::AttachTo(UIWindow* parents)
		{
			parents->AddChild(this);
		}
		void UIWindow::AddChild(UIWindow* child)
		{
			this->_child.push_back(child);
			child->_parent = this;
			child->_root = this->_root;
		}

		void UIWindow::SetHiddenState(bool is)
		{
			for (int i = 0; i < _child.size(); ++i)
			{
				_child[i]->SetHiddenState(is);
			}

			_isHidden = is;

			if (_isHidden)
			{
				_isMouseOver = false;
				_isMouseClick = false;
			}
		}

		void UIWindow::SetPosition(float x, float y)
		{
			_position.x = x;
			_position.y = y;
		}
		POINT UIWindow::GetPosition()
		{
			POINT result;
			result.x = _position.x;
			result.y = _position.y;
			return result;
		}
		void UIWindow::SetSize(int width, int height)
		{
			_size.width = width;
			_size.height = height;

			UpdateTextureSizeMatrix();
		}

		WindowSize UIWindow::GetSize()
		{
			return _size;
		}

		POINT UIWindow::GetFinalPosition()
		{
			POINT pos;
			pos.x = _position.x;
			pos.y = _position.y;

			if (_parent != NULL)
			{
				pos.x += _parent->GetPosition().x;
				pos.y += _parent->GetPosition().y;
			}

			return pos;
		}

		void UIWindow::SetDrawBoundingState(bool is)
		{
			for (int i = 0; i < _child.size(); ++i)
			{
				_child[i]->SetDrawBoundingState(is);
			}

			_isDrawBounding = is;
		}

		void UIWindow::SetBackground(LPDIRECT3DTEXTURE9 tex, D3DXIMAGE_INFO info)
		{
			if (_texture) _texture->Release();

			_texture = tex;

			_texture->AddRef();
			_textureInfo = info;

			UpdateTextureSizeMatrix();
		}

		void UIWindow::SetBackground(char* path)
		{
			if (_texture) _texture->Release();

			D3DXIMAGE_INFO info;
			_texture = TEXTURE_MGR->GetTexture(path, &info);

			_texture->AddRef();
			_textureInfo = info;

			UpdateTextureSizeMatrix();
		}

		UIWindow* UIWindow::GetWindowByTag(UINT num)
		{
			if (GetTagNum() == num) return this;
			
			UIWindow* result = NULL;

			for (int i = 0; i < _child.size(); ++i)
			{
				if (_child[i]->GetTagNum() == num) return _child[i];

				result = _child[i]->GetWindowByTag(num);

				if (result) break;
			}

			return result;
		}

		bool UIWindow::IsMouseOver()
		{
			for (int i = 0; i < _child.size(); ++i)
			{
				if (_child[i]->IsThisMouseOver())
					return true;
				else if (_child[i]->IsMouseOver())
					return true;

			}

			return _isMouseOver;
		}

		void UIWindow::Toggle()
		{
			SetHiddenState(!IsHidden());//IsHidden()
		}

		void UIWindow::UpdateTextureSizeMatrix()
		{
			if (!_texture) return;

			D3DXMatrixIdentity(&_matSize);
			D3DXMatrixScaling(&_matSize, (float)_size.width / (float)_textureInfo.Width, (float)_size.height / (float)_textureInfo.Height, 0);
		}
	}
}