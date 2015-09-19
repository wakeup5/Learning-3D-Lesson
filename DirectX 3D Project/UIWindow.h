#pragma once
namespace NS_ROOT
{
	namespace NS_UI
	{
#define DELIGATEFUNCTION(func) virtual UINT func(UIWindow*, UIWindow*){ return 0; } 

		enum RETURNVALUE
		{
			RETURN_DEFAULT,
			RETURN_OK,
			RETURN_NO,
			RETURN_CANSLE,
			RETURN_EXIT,
			RETURNVALUE_LENGTH
		};

		class UIWindow;
		interface UIDeligate
		{
		protected:
			friend class UIWindow;

			DELIGATEFUNCTION(OnClick);
			DELIGATEFUNCTION(OnClickDown);
			DELIGATEFUNCTION(OnClickUp);
			DELIGATEFUNCTION(OnDrag);
			DELIGATEFUNCTION(OnMouseOver);
			DELIGATEFUNCTION(OnMouseOut);
		};

		class UIWindow : public NS_OBJECTS::Object
		{
		public:
			friend class UIDeligateDefault;

			UIWindow();
			virtual ~UIWindow();

			virtual void Setup();
			virtual void Release();
			virtual void Update();
			virtual void Render(LPD3DXSPRITE sprite);

			void SetDeligate(UIDeligate* deligate){ _deligate = deligate; }

			void AttachTo(UIWindow* parents);
			void AddChild(UIWindow* child);

			void SetHiddenState(bool is);
			bool IsHidden() { return _isHidden; }
			void SetDrawBoundingState(bool is);
			bool IsDrawBounding() { return _isDrawBounding; }

			void SetBackground(LPDIRECT3DTEXTURE9 tex, D3DXIMAGE_INFO info);
			void SetBackground(char* path);
			void SetPosition(float x, float y);
			POINT GetPosition();
			void SetSize(int width, int height);
			WindowSize GetSize();

			POINT GetFinalPosition();

			void SetTagNum(UINT num) { _tagNum = num; }
			UINT GetTagNum() { return _tagNum; }

			UIWindow* GetWindowByTag(UINT num);
			
			bool IsMouseOver();

			void Toggle();
		protected:
			void UpdateTextureSizeMatrix();

			bool IsThisMouseOver() { return _isMouseOver; }

			
		//private:
			//위치와 크기
			D3DXVECTOR3 _position;
			WindowSize _size;

			UIDeligate* _deligate;

			UIWindow* _root;
			UIWindow* _parent;
			std::vector<UIWindow*> _child;

			//텍스쳐
			LPDIRECT3DTEXTURE9 _texture;
			D3DXIMAGE_INFO _textureInfo;
			//LPD3DXSPRITE _sprite;

			//숨김
			bool _isHidden;

			//텍스쳐 사이즈 셋팅하려는 매트릭스
			D3DXMATRIXA16 _matSize;

			//이벤트 관련
			bool _isMouseOver;
			bool _isMouseClick;
			
			//테두리 그림?
			bool _isDrawBounding;

			//윈도우 구분하기 위한 태그번호
			UINT _tagNum;

		};

		class UIDeligateDefault : public UIDeligate
		{
		//private:
		protected:
			friend class UIWindow;

			POINT _clickDownPt;
			POINT _clickDownWindowPt;
			POINT _clickUpPt;
			POINT _clickUpWindowPt;
			POINT _prevClickPt;

			inline virtual UINT OnClick(UIWindow* caller, UIWindow* root) override
			{
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnClickDown(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("클릭 다운!");
				_clickDownPt = GS.mousePos;
				_clickDownWindowPt = caller->GetPosition();
				//_clickUpPt = { 0, 0 };
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnClickUp(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("클릭 업!");
				_clickUpPt = GS.mousePos;
				_clickUpWindowPt = caller->GetPosition();
				//_clickDownPt = { 0, 0 };
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnMouseOver(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("마우스 인!");
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnMouseOut(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("마우스 아웃!");
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnDrag(UIWindow* caller, UIWindow* root) override
			{
				//if (caller != root) return RETURN_DEFAULT;
				//if (caller->_root != caller) return RETURN_DEFAULT;

				POINT pt;
				pt.x = GS.mousePos.x - _clickDownPt.x;
				pt.y = GS.mousePos.y - _clickDownPt.y;

				pt.x += _clickDownWindowPt.x;
				pt.y += _clickDownWindowPt.y;

				caller->SetPosition(pt.x, pt.y);

				_prevClickPt = GS.mousePos;

				return RETURN_DEFAULT;
			}
		};
	}
}