#include "StdAfx.h"
#include "MyUtil.h"


namespace NS_ROOT
{
	namespace NS_UTIL 
	{
		//마우스위치
		POINT GetMousePos()
		{
			POINT mousePos;
			GetCursorPos(&mousePos);	//마우스 Screen 상의 위치를 얻어준다.

			//Screen 상의 위치를 Client 영영역 범위로 바꾼다.
			ScreenToClient(g_hWnd, &mousePos);

			return mousePos;
		}

		//마우스위치 셋팅
		void SetMousePos(int x, int y)
		{
			POINT setMousePos;
			setMousePos.x = x;
			setMousePos.y = y;

			//Client 상의 위치를 Screen 영영역 범위로 바꾼다.
			ClientToScreen(g_hWnd, &setMousePos);

			//SetCursorPos 는   Screen 상의 위치로 셋팅해야한다.
			SetCursorPos(setMousePos.x, setMousePos.y);
		}

		//value 값을 min max 사이로 맞추줌
		float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;

			return value;

		}

		//value 값 0 ~ 1 사일로 맞춤
		float Clamp01(float value)
		{
			if (value < 0.0f)
				return 0.0f;
			else if (value > 1.0f)
				return 1.0f;

			return value;
		}

		float ClampMinusOnePlusOne(float value)
		{
			if (value < -1.0f)
				return -1.0f;
			else if (value > 1.0f)
				return 1.0f;

			return value;
		}

		//float 선형 보간 
		//( t 는 0 ~ 1 사이의 값을 받는데...)
		//( t 가 0 일수록 from 가까운 값이 리턴되고 )
		//( t 가 1 일수록 to 가까운 값이 리턴된다 )
		float Lerp(float from, float to, float t)
		{
			t = Clamp01(t);

			float delta = to - from;

			return (delta * t) + from;
		}

		//float 선형 보간 반대
		//value 값이 head 와 rear 사이에 어느정도 위치에 있는지
		//0~1 사이의 값으로 리턴한다.
		//						 5			 9			7 
		float InverseLerp(float head, float rear, float value)
		{
			float delta = rear - head;			// 4
			float inValue = value - head;		// 2

			if (inValue < 0)
				inValue = 0;

			return inValue / delta;
		}

		//벡터 선형 보간
		D3DXVECTOR3 VecLerp(const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t)
		{
			D3DXVECTOR3 result(
				Lerp(from.x, to.x, t),
				Lerp(from.y, to.y, t),
				Lerp(from.z, to.z, t));

			return result;
		}

		//Random
		void SetRandomSeed()
		{
			srand(GetTickCount());
		}

		float RandomFloatRange(float min, float max)
		{
			//0 ~ 99999
			// 0 ~ 1 까지의 실수

			float factor = (rand() % 1001) * 0.001f;

			float delta = (max - min);

			float result = (delta * factor) + min;

			return result;

		}
		int RandomIntRange(int min, int max)
		{
			int delta = max - min;

			return (rand() % delta) + min;
		}

		//정점의 노말을 계산해주는 함수
		void ComputeNormal(
			D3DXVECTOR3* pNorams,			//결과로 받을 노말백터 배열 포인터 ( 노말벡터의 배열의 수는 정점 배열의 수와 같다 )
			const D3DXVECTOR3* pVertices,	//계산에 사용된 정점위치 배열 포인터
			int verticesNum,				//정점 갯수
			const DWORD* pIndices,			//인덱스 배열포인터 ( 일단 인덱스는 DWORD 로 대동단결 )
			int indicesNum					//인덱스 배열포인터 갯수
			)
		{
			//노말 결과 털고 시작
			ZeroMemory(pNorams, sizeof(D3DXVECTOR3) * verticesNum);


			//삼각형 갯수
			DWORD triNum = indicesNum / 3;
			for (DWORD i = 0; i < triNum; i++)
			{
				//해당 삼각형의 정점 인덱스
				DWORD i0 = pIndices[(i * 3) + 0];
				DWORD i1 = pIndices[(i * 3) + 1];
				DWORD i2 = pIndices[(i * 3) + 2];

				//정점 3개
				D3DXVECTOR3 v0 = pVertices[i0];
				D3DXVECTOR3 v1 = pVertices[i1];
				D3DXVECTOR3 v2 = pVertices[i2];

				//Edge
				D3DXVECTOR3 edge1 = v1 - v0;
				D3DXVECTOR3 edge2 = v2 - v0;

				//Cross
				D3DXVECTOR3 cross;
				D3DXVec3Cross(&cross, &edge1, &edge2);

				//Normal
				D3DXVECTOR3 normal;
				D3DXVec3Normalize(&normal, &cross);

				//증가 시킨다.
				pNorams[i0] += normal;
				pNorams[i1] += normal;
				pNorams[i2] += normal;
			}

			//최종 적으로 Normalvector 정규화한다.
			for (DWORD i = 0; i < verticesNum; i++)
			{
				D3DXVec3Normalize(&pNorams[i], &pNorams[i]);
			}
		}

		float GetDistance(const D3DXVECTOR3 &p1, const D3DXVECTOR3 &p2)
		{
			D3DXVECTOR3 temp = p2 - p1;
			return sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));
		}

		bool IntersectSphere(Ray r, Sphere &s)
		{
			D3DXMATRIXA16 matPos, matPosInv;
			D3DXMatrixTranslation(&matPos, s.x, s.y, s.z);

			D3DXMatrixInverse(&matPosInv, NULL, &matPos);

			D3DXVec3TransformCoord(&r.origin, &r.origin, &matPosInv);
			D3DXVec3TransformCoord(&r.origin, &r.origin, &matPosInv);

			float b = D3DXVec3Dot(&r.origin, &r.direction);
			float a = D3DXVec3Dot(&r.direction, &r.direction);
			float c = (r.origin.x * r.origin.x + r.origin.y * r.origin.y + r.origin.z * r.origin.z) - (s.radius * s.radius);

			if (b * b - a * c >= 0) return true;

			return false;
		}

		Ray GetRayByMousePos(float x, float y)
		{
			Ray result;
			float px, py;

			D3DVIEWPORT9 vp;
			D3DXMATRIXA16 proj, view, viewInv;
			//뷰포트돠 투영 정보를 이용해서 카메라 좌표를 얻는다.
			DEVICE->GetViewport(&vp);
			DEVICE->GetTransform(D3DTS_PROJECTION, &proj);

			px = (((2.0f * x) / vp.Width) - 1.0f) / proj._11;
			py = (((-2.0f * y) / vp.Height) + 1.0f) / proj._22;

			result.origin = D3DXVECTOR3(0, 0, 0);
			result.direction = D3DXVECTOR3(px, py, 1);
			//카메라 좌표를 월드 좌표계로 이동

			DEVICE->GetTransform(D3DTS_VIEW, &view);
			D3DXMatrixInverse(&viewInv, NULL, &view);

			D3DXVec3TransformCoord(&result.origin, &result.origin, &viewInv);
			D3DXVec3TransformNormal(&result.direction, &result.direction, &viewInv);
			D3DXVec3Normalize(&result.direction, &result.direction);

			return result;
		}
		bool IntersectPolygon(Ray r, D3DXVECTOR3 * arrVector, D3DXVECTOR3 *colisPos)
		{
			bool result;
			D3DXVECTOR3 temp;
			float u, v;

			result = D3DXIntersectTri(
				&arrVector[0],
				&arrVector[1],
				&arrVector[2],
				&r.origin,
				&r.direction,
				&u, &v, NULL);
			
			//충돌한 지점 구하기

			temp = arrVector[0] + u * (arrVector[1] - arrVector[0]) + v * (arrVector[2] - arrVector[0]);

			if (colisPos) *colisPos = temp;

			return result;
		}
	}
}