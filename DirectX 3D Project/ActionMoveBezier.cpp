#include "stdafx.h"
#include "ActionMoveBezier.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		int GetTotalSum(int num)
		{
			if (num == 0) 
				return 0;
			else if (num == 1)
				return 1;
			else
				return GetTotalSum(num - 1) * num;
		}

		D3DXVECTOR3 GetPosition22222(std::vector<D3DXVECTOR3> &p, float t)
		{
			if (p.size() == 1) return p[0];

			std::vector<D3DXVECTOR3> temp;

			for (int i = 0; i < p.size() - 1; i++)
			{
				temp.push_back((1.0f - t) * p[i] + t * p[i + 1]);
			}

			return GetPosition22222(temp, t);
		}

		ActionMoveBezier::ActionMoveBezier()
		{
		}


		ActionMoveBezier::~ActionMoveBezier()
		{
		}

		void ActionMoveBezier::Start()
		{
			_startTime = TIME_MGR->GetLastTime();
			_currentTime = 0.0f;

			if (_object)
			{
				_object->SetWorldPosition(_points[0]);
			}
		}

		void ActionMoveBezier::Update()
		{
			_currentTime = (TIME_MGR->GetLastTime() - _startTime);

			if (_points.empty())
			{
				if (_deligate)
					_deligate->OnActionFinish();
			}

			if (_currentTime > _actionTime)
			{
				_object->SetWorldPosition(_points[_points.size() - 1]);
				if (_deligate)
					_deligate->OnActionFinish();
			}
			else
			{
				float t = _currentTime / _actionTime;

				D3DXVECTOR3 p = { 0, 0, 0 }, temp;
				float f = 1, m, b;

				/*
				//Facto(row) / ((Facto(row - col)) * Facto(col))
				for (int k = 0, n = _points.size(); k < n; k++)
				{
					if ((GetTotalSum(k) * GetTotalSum(n - k)) == 0) 
						f = 1;
					else
						f = GetTotalSum(n) / (GetTotalSum(n - k) * GetTotalSum(k));

					m = pow(t, k);
					b = pow((1 - t), n - k);

					temp = f * m * b * _points[k];
					p += temp;
				}
				*/
				p = GetPosition22222(_points, t);
				
				//p = (1.0f - t) * _points[0] + t * _points[1];

				LOG_MGR->AddLog("%f, %f, %f", p.x, p.y, p.z);

				_object->SetWorldPosition(p);
				D3DXVECTOR3 vDir = p - _prevPosition;
				D3DXVec3Normalize(&vDir, &vDir);
				_object->LookDirection(vDir);
				_prevPosition = p;
			}
		}
	}
}