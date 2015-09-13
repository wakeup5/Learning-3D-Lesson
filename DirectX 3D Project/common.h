#pragma once

//namespace
#define NS_ROOT		wakeup
#define NS_BASE		Base
#define NS_UTIL		Util
#define NS_DIRECTX	DirectX
#define NS_OBJECTS	Objects

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

#define BG_COLOR	D3DCOLOR_XRGB(127, 127, 255)

//vertex
typedef struct tagPC_VERTEX
{
	D3DXVECTOR3 p;
	DWORD		c;
	static enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

	tagPC_VERTEX() 
	{
		tagPC_VERTEX(0, 0, 0, 0);
	}
	tagPC_VERTEX(D3DXVECTOR3 pos)
	{
		tagPC_VERTEX(pos.x, pos.y, pos.z, 0);
	}
	tagPC_VERTEX(float x, float y, float z)
	{
		tagPC_VERTEX(x, y, z, 0);
	}
	tagPC_VERTEX(D3DXVECTOR3 pos, D3DCOLOR color)
	{
		tagPC_VERTEX(pos.x, pos.y, pos.z, color);
	}
	tagPC_VERTEX(float x, float y, float z, D3DCOLOR color)
	{
		ZeroMemory(&p, sizeof(p));
		p.x = x;
		p.y = y;
		p.z = z;

		c = color;
	}
} PC_VERTEX, FAR *LPPC_VEREX;

typedef struct tagPT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;
	static enum { FVF = D3DFVF_XYZ | D3DFVF_TEX0 };

	tagPT_VERTEX() 
	{
		tagPT_VERTEX(0, 0, 0, 0, 0);
	}
	tagPT_VERTEX(float x, float y, float z)
	{
		tagPT_VERTEX(x, y, z, 0, 0);
	}
	tagPT_VERTEX(float x, float y, float z, float u, float v)
	{
		p = D3DXVECTOR3(x, y, z);
		t = D3DXVECTOR2(u, v);
	}
} PT_VERTEX, FAR *LPPT_VEREX;