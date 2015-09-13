#pragma once

#include "Singleton.h"
namespace NS_ROOT
{
	namespace NS_UTIL
	{
		class TimeMgr : public Singleton<TimeMgr>
		{
		private:
			bool			m_bHardWare;		//������ Ÿ�̸� ���� ����

			__int64			m_nPreriodTime;		//1�ʿ� ���ī��Ʈ �ϴ°�?
			__int64			m_nLastTime;		//������ ������ �ð�
			__int64			m_nCurTime;			//���� �ð�
			__int64			m_nDeltaTime;		//���� �����Ӱ� �����ð�

			double			m_TimeScaleSec;		//1ī��Ʈ ����.
			double			m_FrameDeltaSec;	//�������� ��� ��
			double			m_TotalSec;			//���α׷� ������ ����ð�.

			double			m_FrameCountSec;		//������ ���� �ð�
			DWORD			m_FrameCount;		//������ ī��Ʈ
			DWORD			m_FramePerSec;		//�ʴ� ������



		private:
			TimeMgr(void);

		public:
			//Ư�� �Լ��� ���� ģ�� ����
			friend TimeMgr* Singleton<TimeMgr>::GetInstance();

			~TimeMgr(void);

			HRESULT Setup(void);
			void Release(void);

			//�ž�����Ʈ �����ش�.
			void UpdateTime(float frameLock = 0.0f);

			//Ÿ�������� ����Ѵ�
			void DrawTimeInfo();

			//�����Ӱ��� ���� �ʽð��� ��´�.
			double GetFrameDeltaSec(void) {
				return m_FrameDeltaSec;
			}


		};
	}
}

#define TIME_MGR NS_ROOT::NS_UTIL::TimeMgr::GetInstance()