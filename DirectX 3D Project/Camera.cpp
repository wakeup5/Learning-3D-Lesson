#include "StdAfx.h"
#include "Camera.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Camera::Camera(void)
		{
			//기본화각 60 도
			this->fov = 60.0f * ONE_RAD;

			//기본 Near
			this->camNear = 0.1f;

			//기본 Far
			this->camFar = 1000.0f;

		}


		Camera::~Camera(void)
		{
		}




		//투영행렬과 View 행렬을 업데이트
		void Camera::UpdateMatrix()
		{
			//화각에 의한 Projection 행렬 업데이트
			D3DXMatrixPerspectiveFovLH(
				&matProjection,
				this->fov,
				static_cast<float>(WINSIZE_X) / static_cast<float>(WINSIZE_Y),
				this->camNear,
				this->camFar);

			//뷰행렬 카메라 월드위치에 대한 역행렬이다.
			D3DXMatrixInverse(&matView, NULL, &matFinal);


			this->matViewProjection = this->matView * this->matProjection;


		}

		//View 행렬과 투영 행렬을 셋팅
		void Camera::UpdateCamToDevice(LPDIRECT3DDEVICE9 pDevice)
		{
			//행렬 업데이트 해주고 
			this->UpdateMatrix();

			//셋팅
			pDevice->SetTransform(D3DTS_VIEW, &this->matView);
			pDevice->SetTransform(D3DTS_PROJECTION, &this->matProjection);


		}
	}
}