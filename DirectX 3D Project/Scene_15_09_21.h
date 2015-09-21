#pragma once
#include "Scene.h"
#include "cFrame.h"
#include "cAseLoader.h"
#include "Camera.h"
#include "ActionMoveBezier.h"

using namespace wakeup;
using namespace wakeup::Util;
using namespace wakeup::Objects;
using namespace wakeup::Util;
using namespace wakeup::Base;
//using namespace wakeup::UI;

namespace S15_09_21
{
	class Woman : public ActionObject, public ActionDeligate
	{
	public:
		cFrame* m_pRootRun;
		cFrame* m_pRootSt;
		cFrame* m_pRootWoman;

		ActionMoveBezier* _bAction;
	public:
		Woman()
		{
			cAseLoader l;
			m_pRootRun = l.Load("woman/woman_01_all.ASE");
			m_pRootSt = l.Load("woman/woman_01_all_stand.ASE");
			m_pRootWoman = m_pRootSt;

			SetLocalPosition(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10));

			_bAction = new ActionMoveBezier;
			_bAction->ClearPoint();
			_bAction->AddPoint(GetWorldPosition());
			_bAction->AddPoint(D3DXVECTOR3(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10)));
			_bAction->SetActionTime(1);

			SetAction(_bAction);
			_bAction->SetDeligate(this);
			_bAction->Start();
		}
		~Woman()
		{
			SAFE_RELEASE(m_pRootRun);
			SAFE_RELEASE(m_pRootSt);
		}
		virtual void Update()
		{
			if (_action)
			{
				_action->Update();

				if (m_pRootWoman != m_pRootRun) m_pRootWoman = m_pRootRun;
			}
			else
			{
				if (m_pRootWoman != m_pRootSt) m_pRootWoman = m_pRootSt;
			}

			int nKeyFrame = (GetTickCount() * 10) % (3200 - 640) + 640;
			m_pRootWoman->Update(nKeyFrame, &GetFinalMatrix());
		}

		void Render()
		{
			m_pRootWoman->Render();
		}

		virtual void OnActionFinish()
		{
			_bAction->ClearPoint();
			_bAction->AddPoint(GetWorldPosition());
			_bAction->AddPoint(D3DXVECTOR3(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10)));
			_bAction->Start();

			//_action = NULL;
		}
	};
}


class Scene_15_09_21 :
	public Scene
{
private:
	cFrame* m_pRootRun;
	cFrame* m_pRootSt;
	S15_09_21::Woman* _woman[3];

	Camera* _cam;
	Transform _m[3];

	ActionMoveBezier* _acMove[3];
public:
	Scene_15_09_21();
	~Scene_15_09_21();

	virtual HRESULT Setup();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();
};
