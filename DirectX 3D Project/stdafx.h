// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <assert.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//DirectX Header Include
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//헤더 추가
#include "common.h"
#include "MyUtil.h"
#include "Singleton.h"
#include "Device.h"

#include "DXFontManager.h"
#include "GizmoManager.h"
#include "TimeMgr.h"
#include "LogMgr.h"
#include "KeyMgr.h"
#include "TextureManager.h"

//공통 오브젝트
#include "Transform.h"
#include "Camera.h"
#include "Object.h"

//씬
#include "Scene.h"

extern HWND g_hWnd;
extern GameSystem GS;

//오브젝트 로더, ase 로더

#define SAFE_RELEASE(p) { if(p) p->Release(); p = NULL; }
#define SAFE_DELETE(p) { if(p) delete p; p = NULL; }
#define SAFE_ADD_REF(p) { if(p) p->AddRef(); }

#define SINGLETONE(class_name) \
	private: \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
		}\
}


struct ST_POS_SAMPLE
{
	int				n;
	D3DXVECTOR3		v;

	ST_POS_SAMPLE()
		: n(0)
		, v(0, 0, 0)
	{
	}
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;

	ST_ROT_SAMPLE()
		: n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager.h"