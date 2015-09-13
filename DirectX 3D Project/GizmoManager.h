#pragma once
#include "singleton.h"


#define CIRCLEGIZMO_SEGMENTS 36

namespace NS_ROOT
{
	namespace NS_UTIL
	{
		class GizmoManager : public Singleton < GizmoManager >
		{
		private:
			typedef struct tagGIZMOVERTEX {
				D3DXVECTOR3 pos;
				DWORD color;
				enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
			}GIZMOVERTEX, *LPGIZMOVERTEX;


		private:
			LPDIRECT3DDEVICE9		m_pDevice;									//���� Device;
			D3DXVECTOR3				m_pCirclePos[CIRCLEGIZMO_SEGMENTS + 1];	//Circle �� ���� ��ġ


		public:
			GizmoManager(void);
			~GizmoManager(void);


			HRESULT Setup(LPDIRECT3DDEVICE9	device);
			void Release() override;

			//���� �׸��� �Լ�
			void Line(const D3DXVECTOR3& startPos, const D3DXVECTOR3& endPos, DWORD color = 0xff808080) const;

			//���� �׸��带 �׸��� �Լ�
			void WorldGrid(float cellSize, int cellNum) const;

			//���� �׸��� �Լ�
			void Circle(const D3DXVECTOR3& centerPos, float radius, const D3DXVECTOR3& axis = D3DXVECTOR3(0, 0, 1), DWORD color = 0xff808080) const;

			//���̾� ���� �׸��� �Լ�
			void WireSphere(const D3DXVECTOR3& centerPos, float radius, DWORD color = 0xff808080) const;

			//���� AABB Box �� �׸��� �Լ�
			void AABBBox(const D3DXVECTOR3& minPos, const D3DXVECTOR3& maxPos, DWORD color = 0xff808080) const;




		};
	}
}
#define GIZMO_MGR		NS_ROOT::NS_UTIL::GizmoManager::GetInstance()