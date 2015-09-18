#pragma once
namespace NS_ROOT
{
	namespace NS_UI
	{
#define DELIGATEFUNCTION(func) virtual UINT func(UIWindow*, UIWindow*){ return 0; } 
		
		typedef struct tagWindowSize
		{
			int width;
			int height;
			tagWindowSize(){}
			tagWindowSize(int w, int h)
			{
				width = w;
				height = h;
			}
		} WindowSize;

		class UIWindow;
		interface UIDeligate
		{
		protected:
			DELIGATEFUNCTION(OnClick);
			DELIGATEFUNCTION(OnClickDown);
			DELIGATEFUNCTION(OnClickUp);
			DELIGATEFUNCTION(OnMouseOver);
			DELIGATEFUNCTION(OnMouseOut);

			friend class UIWindow;
		};

		class UIWindow : public NS_OBJECTS::Object
		{
		public:
			UIWindow();
			virtual ~UIWindow();

			virtual void Setup();
			//virtual void Release();
			virtual void Update();
			virtual void Render(LPD3DXSPRITE sprite);

			void SetDeligate(UIDeligate* deligate){ _deligate = deligate; }

			void AttachTo(UIWindow* parents);
			void AddChild(UIWindow* child);

		protected:
			void SetPosition(float x, float y);
			void SetSize(int width, int height);
			
			void SetBackground();
		private:
			//위치와 크기
			D3DXVECTOR3 _position;
			WindowSize _size;

			UIDeligate* _deligate;

			UIWindow* _root;
			std::vector<UIWindow*> _childWindow;

			//텍스쳐
			LPDIRECT3DTEXTURE9 _background;

			//LPD3DXSPRITE _sprite;


			friend interface UIDeligate;
		};
	}
}