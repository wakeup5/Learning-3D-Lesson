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

//System ���� (DirectSDK ��ġ����/Include) ��� ���
//�ַ��Ž���⿡�� ������Ʈ ��Ŭ��
//�Ӽ�
//�����Ӽ��� VC++ ���͸� �׸���
//â�� ����������.
//���Ե��丮ĭ�� �����ӹ��ڿ������� �����ϸ� ������ �Ʒ�ȭ��ǥ Ŭ��
//<����..> ���ڸ�Ŭ��
//���Ե��丮 â�� �����鼭 ���� ����� �����߰� ������Ŭ��
//Ŭ���ؼ� ������ �� ������ ... ��ư ����
//Ž���� �����鼭 (DirectSDK ��ġ����/Include) ����


//�ʿ���̺귯�� (DirectSDK ��ġ����/Lib/x86)
//d3dx9.lib
//d3d9.lib
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" )
//#pragma comment( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//��� �߰�
#include "common.h"