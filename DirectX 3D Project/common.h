#pragma once

//namespace
#define NS_ROOT		wakeup
#define NS_BASE		Base
#define NS_UTIL		Util
#define NS_DIRECTX	DirectX
#define NS_OBJECTS	Objects
#define NS_UI		UI

//macro
#define SAFE_RELEASE(p) {if ((p) != NULL) (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) {if((p) != NULL) delete (p); (p) = NULL; }
//define
#define WINSIZE_X	1280		//초기 윈도우 가로 크기
#define WINSIZE_Y	800			//초기 윈도우 세로 크기
#define WINPOS_X	0			//초기 윈도우 시작 위치 X
#define WINPOS_Y	0			//초기 윈도우 시작 위치 Y
#define WIN_CLASS	"Windows Exam"		//윈도우 클레스 이름
#define WIN_TITLE	"Windows Exam"		//윈도우 타이틀 이름
#define WIN_STYLE	WS_OVERLAPPEDWINDOW	//윈도우 형태

#define BG_COLOR	D3DCOLOR_XRGB(63, 63, 63)

//vertex
typedef struct tagPC_VERTEX
{
	D3DXVECTOR3 p = { 0, 0, 0 };
	DWORD		c = 0;
	static enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

	tagPC_VERTEX() 
	{

	}
	tagPC_VERTEX(D3DXVECTOR3 pos)
	{
		p = pos;
		c = 0;
	}
	tagPC_VERTEX(float x, float y, float z)
	{
		p = D3DXVECTOR3(x, y, z);
		c = 0;
	}
	tagPC_VERTEX(D3DXVECTOR3 pos, D3DCOLOR color)
	{
		p = pos;
		c = color;
	}
	tagPC_VERTEX(float x, float y, float z, D3DCOLOR color)
	{
		p = D3DXVECTOR3(x, y, z);
		c = color;
	}
} PC_VERTEX, FAR *LPPC_VEREX;

typedef struct tagPT_VERTEX
{
	D3DXVECTOR3 p = { 0, 0, 0 };
	D3DXVECTOR2	t = { 0, 0 };
	static enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };

	tagPT_VERTEX() 
	{

	}
	tagPT_VERTEX(D3DXVECTOR3 &pos)
	{
		p = pos;
	}
	tagPT_VERTEX(float x, float y, float z)
	{
		p = D3DXVECTOR3(x, y, z);
	}
	tagPT_VERTEX(D3DXVECTOR3 &pos, D3DXVECTOR2 &tex)
	{
		p = pos;
		t = tex;
	}
	tagPT_VERTEX(float x, float y, float z, float u, float v)
	{
		p = D3DXVECTOR3(x, y, z);
		t = D3DXVECTOR2(u, v);
	}
} PT_VERTEX, FAR *LPPT_VEREX;

typedef struct tagPNT_VERTEX
{
	D3DXVECTOR3 p = { 0, 0, 0 };
	D3DXVECTOR3	n = { 0, 0, 0 };
	D3DXVECTOR2 t = { 0, 0 };
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };

	tagPNT_VERTEX()
	{

	}
	tagPNT_VERTEX(float x, float y, float z)
	{
		p = D3DXVECTOR3(x, y, z);
	}
	tagPNT_VERTEX(D3DXVECTOR3 pos)
	{
		p = pos;
	}
	tagPNT_VERTEX(float x, float y, float z, float nx, float ny, float nz)
	{
		p = D3DXVECTOR3(x, y, z);
		n = D3DXVECTOR3(nx, ny, nz);
	}
	tagPNT_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR3 nor)
	{
		p = pos;
		n = nor;
	}
	tagPNT_VERTEX(float x, float y, float z, float nx, float ny, float nz, float u, float v)
	{
		p = D3DXVECTOR3(x, y, z);
		n = D3DXVECTOR3(nx, ny, nz);
		t = D3DXVECTOR2(u, v);
	}
	tagPNT_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXVECTOR2 tex)
	{
		p = pos;
		n = nor;
		t = tex;
	}

} PNT_VERTEX, FAR *LPPNT_VERTEX;

typedef struct tagPNC_VERTEX
{
	D3DXVECTOR3 p = { 0, 0, 0 };
	D3DXVECTOR3	n = { 0, 0, 0 };
	DWORD c = 0;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE };

	tagPNC_VERTEX()
	{

	}
	tagPNC_VERTEX(float x, float y, float z)
	{
		p = D3DXVECTOR3(x, y, z);
	}
	tagPNC_VERTEX(D3DXVECTOR3 pos)
	{
		p = pos;
	}
	tagPNC_VERTEX(float x, float y, float z, float nx, float ny, float nz)
	{
		p = D3DXVECTOR3(x, y, z);
		n = D3DXVECTOR3(nx, ny, nz);
	}
	tagPNC_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR3 nor)
	{
		p = pos;
		n = nor;
	}
	tagPNC_VERTEX(float x, float y, float z, float nx, float ny, float nz, D3DXCOLOR color)
	{
		p = D3DXVECTOR3(x, y, z);
		n = D3DXVECTOR3(nx, ny, nz);
		c = color;
	}
	tagPNC_VERTEX(D3DXVECTOR3 pos, D3DXVECTOR3 nor, D3DXCOLOR color)
	{
		p = pos;
		n = nor;
		c = color;
	}

} PNC_VERTEX, FAR *LPPNC_VERTEX;

typedef struct tagRHWC_VERTEX
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
} RHWC_VERTEX, FAR *LPRHWC_VERTEX;

//system struct
typedef struct tagGameSystem
{
	POINT mousePos;
	bool isMouseClick;

	bool isUIClick;
} GameSystem;
//#define GS GameSystem

//struct
namespace NS_ROOT
{
	typedef struct tagWindowSize
	{
		int width;
		int height;
		tagWindowSize() {}
		tagWindowSize(int w, int h)
		{
			width = w;
			height = h;
		}
	} WindowSize;

	typedef struct tagRay
	{
		D3DXVECTOR3 origin;
		D3DXVECTOR3 direction;

		tagRay(){}
	} Ray;

	typedef struct tagSphere
	{
		union
		{
			D3DXVECTOR3 position;
			struct
			{
				float x;
				float y;
				float z;
			};
		};

		float radius;

		tagSphere() {}
	} Sphere;
}