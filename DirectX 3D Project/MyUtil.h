#pragma once


#define	FEPSILON		0.00001f

#define	ABS(a)					( ((a) < 0) ? (a) * -1 : (a) )
#define	FLOATEQUAL( a, b )		( ABS((a) - (b) ) < FEPSILON )
#define	FLOATZERO(a)			( ABS((a)) < FEPSILON )
#define	VECTORZERO(v)			( FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z) )

#define	ONE_RAD			(D3DX_PI / 180)
#define RAD(dgree)		(ONE_RAD * (dgree))

#define	RS(a,b)			DEVICE->SetRenderState((a),(b))		

namespace NS_ROOT
{
	namespace NS_UTIL
	{
		POINT GetMousePos();						//마우스위치
		void SetMousePos(int x, int y);			//마우스위치 셋팅

		float Clamp(float value, float min, float max);	//value 값을 min max 사이로 맞추줌
		float Clamp01(float value);						//value 값 0 ~ 1 사일로 맞춤
		float ClampMinusOnePlusOne(float value);			//value 값 -1 ~ 1 사일로 맞춤

		//float 선형 보간 
		//( t 는 0 ~ 1 사이의 값을 받는데...)
		//( t 가 0 일수록 from 가까운 값이 리턴되고 )
		//( t 가 1 일수록 to 가까운 값이 리턴된다 )
		float Lerp(float from, float to, float t);

		//float 선형 보간 반대
		//value 값이 head 와 rear 사이에 어느정도 위치에 있는지
		//0~1 사이의 값으로 리턴한다.
		float InverseLerp(float head, float rear, float value);

		//벡터 선형 보간
		D3DXVECTOR3 VecLerp(const D3DXVECTOR3& from, const D3DXVECTOR3& to, float t);

		//Random
		void SetRandomSeed();
		float RandomFloatRange(float min, float max);
		int RandomIntRange(int min, int max);

		//정점의 노말을 계산해주는 함수
		void ComputeNormal(
			D3DXVECTOR3* pNorams,			//결과로 받을 노말백터 배열 포인터 ( 노말벡터의 배열의 수는 정점 배열의 수와 같다 )
			const D3DXVECTOR3* pVertices,	//계산에 사용된 정점위치 배열 포인터
			int verticesNum,				//정점 갯수
			const DWORD* pIndices,			//인덱스 배열포인터 ( 일단 인덱스는 DWORD 로 대동단결 )
			int indicesNum					//인덱스 배열포인터 갯수
			);
	}
}