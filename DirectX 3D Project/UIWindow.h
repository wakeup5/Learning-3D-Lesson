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

			void isHidden(bool is);// { _isHidden = is; }

			void SetBackground(LPDIRECT3DTEXTURE9 tex, D3DXIMAGE_INFO info);
			void SetBackground(char* path);
			void SetPosition(float x, float y);
			POINT GetPosition();
			void SetSize(int width, int height);
			WindowSize GetSize();

			POINT GetFinalPosition();

			void IsDrawBounding(bool is);

			void SetTagNum(UINT num) { _tagNum = num; }
			UINT GetTagNum() { return _tagNum; }

			UIWindow* GetWindowByTag(UINT num);
		protected:
			void UpdateTextureSizeMatrix();

			bool isMouseOver() { return _isMouseOver; }
		//private:
			//��ġ�� ũ��
			D3DXVECTOR3 _position;
			WindowSize _size;

			UIDeligate* _deligate;

			UIWindow* _root;
			UIWindow* _parent;
			std::vector<UIWindow*> _child;

			//�ؽ���
			LPDIRECT3DTEXTURE9 _texture;
			D3DXIMAGE_INFO _textureInfo;
			//LPD3DXSPRITE _sprite;

			//����
			bool _isHidden;

			//�ؽ��� ������ �����Ϸ��� ��Ʈ����
			D3DXMATRIXA16 _matSize;

			//�̺�Ʈ ����
			bool _isMouseOver;
			bool _isMouseClick;
			
			//�׵θ� �׸�?
			bool _isDrawBounding;

			//������ �����ϱ� ���� �±׹�ȣ
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
				//LOG_MGR->AddLog("Ŭ�� �ٿ�!");
				_clickDownPt = GS.mousePos;
				_clickDownWindowPt = root->GetPosition();
				//_clickUpPt = { 0, 0 };
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnClickUp(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("Ŭ�� ��!");
				_clickUpPt = GS.mousePos;
				_clickUpWindowPt = root->GetPosition();
				//_clickDownPt = { 0, 0 };
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnMouseOver(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("���콺 ��!");
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnMouseOut(UIWindow* caller, UIWindow* root) override
			{
				//LOG_MGR->AddLog("���콺 �ƿ�!");
				return RETURN_DEFAULT;
			}
			inline virtual UINT OnDrag(UIWindow* caller, UIWindow* root) override
			{
				if (caller != root) return RETURN_DEFAULT;
				//if (caller->_root != caller) return RETURN_DEFAULT;

				POINT pt;
				pt.x = GS.mousePos.x - _clickDownPt.x;
				pt.y = GS.mousePos.y - _clickDownPt.y;

				pt.x += _clickDownWindowPt.x;
				pt.y += _clickDownWindowPt.y;

				root->SetPosition(pt.x, pt.y);

				_prevClickPt = GS.mousePos;

				return RETURN_DEFAULT;
			}
		};
	}
}