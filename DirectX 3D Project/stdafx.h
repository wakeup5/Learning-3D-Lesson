// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//DirectX Header Include
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//��� �߰�
#include "common.h"
#include "MyUtil.h"
#include "Singleton.h"
#include "Device.h"

#include "DXFontManager.h"
#include "GizmoManager.h"
#include "TimeMgr.h"
#include "LogMgr.h"
#include "KeyMgr.h"

//���� ������Ʈ
#include "Transform.h"
#include "Camera.h"

//��
#include "Scene.h"

extern HWND g_hWnd;