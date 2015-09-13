#include "stdafx.h"
#include "Device.h"

namespace NS_ROOT
{
	namespace NS_DIRECTX
	{
		Device::Device()
			: _device(NULL)
		{
		}


		Device::~Device()
		{
		}

		LPDIRECT3DDEVICE9 Device::GetDevice()
		{
			return _device;
		}

		HRESULT Device::Setup()
		{
			if (_device) SAFE_RELEASE(_device);

			LPDIRECT3D9 d3d9;
			d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

			if (d3d9 == NULL) {
				MessageBox(g_hWnd, "Direct3DCreate9() - FAILED", "FAILED", MB_OK);
				return E_FAIL;
			}

			D3DCAPS9	caps;
			d3d9->GetDeviceCaps(
				D3DADAPTER_DEFAULT,		//�� ���÷��� �׷��� ī�� �׳� D3DADAPTER_DEFAULT
				D3DDEVTYPE_HAL,			//����̽�Ÿ�� ���� �׳� D3DDEVTYPE_HAL
				&caps					//����̽� ������ �޾ƿ� D3DCAPS9 ������
				);

			DWORD vertexProcessing = 0;

			if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
				vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
			else
				vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

			D3DPRESENT_PARAMETERS d3dpp;
			d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				//���� ���ۿ� ���׽� ���� ũ�� ���� 24bit ���ٽ� ���� 8 ��Ʈ
			d3dpp.BackBufferCount = 1;						//����۴� �Ѱ�
			d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;			//����� ���� ���� ����8��Ʈ,����8��Ʈ,�׸�8��Ʈ,���8��Ʈ
			d3dpp.BackBufferHeight = WINSIZE_Y;				//����� �ȼ� ���� ũ��
			d3dpp.BackBufferWidth = WINSIZE_X;				//����� �ȼ� ���� ũ��
			d3dpp.EnableAutoDepthStencil = true;						//�ڵ� ���̹��� ��� ���� ( �׳� true )
			d3dpp.Flags = 0;						//�ϴ� 0
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//ȭ�� �ֻ��� ( �׳� D3DPRESENT_RATE_DEFAULT ����� �ֻ����� ���Ͻ� )
			d3dpp.hDeviceWindow = g_hWnd;					//Device �� ��µ� ������ �ڵ�
			d3dpp.MultiSampleQuality = 0;						//��Ƽ ���ø� �� 
			d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;		//��Ƽ ���ø� Ÿ�� ( D3DMULTISAMPLE_NONE ��Ƽ�˸��ƽ� ������ ) 
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	//ȭ�� ���� ���� ( �׳� D3DPRESENT_INTERVAL_ONE ����� �ֻ����� ���Ͻ� )
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ȭ�� ���� ü�� ��� ( D3DSWAPEFFECT_DISCARD )
			d3dpp.Windowed = true;

			HRESULT result = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,			//�� ���÷��� �׷��� ī�� �׳� D3DADAPTER_DEFAULT
				D3DDEVTYPE_HAL,				//����̽�Ÿ�� ���� �׳� D3DDEVTYPE_HAL
				g_hWnd,						//����̽��� ����� ������ �ڵ�
				vertexProcessing,			//���� ó�� ��Ŀ� ���� �÷���
				&d3dpp,						//�տ��� ������ D3DPRESENT_PARAMETERS ����ü ������
				&_device);				//���� ����̽� ����������

			if (FAILED(result))
			{
				d3d9->Release();
				d3d9 = NULL;

				MessageBox(g_hWnd, "CreateDevice() - FAILED", "FAILED", MB_OK);
				return E_FAIL;
			}

			d3d9->Release();
			d3d9 = NULL;
			return S_OK;
		}

		void Device::Release()
		{
			SAFE_RELEASE(_device);
		}
	}
}
