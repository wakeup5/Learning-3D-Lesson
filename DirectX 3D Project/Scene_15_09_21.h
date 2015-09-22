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

		D3DLIGHT9 _light;
		DWORD _lightNum;

		static DWORD _lightIndex;
	public:
		Woman()
		{
			cAseLoader l;
			m_pRootRun = l.Load("woman/woman_01_all.ASE");
			m_pRootSt = l.Load("woman/woman_01_all_stand.ASE");
			m_pRootWoman = m_pRootSt;

			SetLocalPosition(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10));

			_bAction = new ActionMoveBezier;
			//_bAction->ClearPoint();
			//_bAction->AddPoint(GetWorldPosition());
			//_bAction->AddPoint(D3DXVECTOR3(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10)));
			_bAction->SetActionTime(1);

			//SetAction(_bAction);
			_bAction->SetDeligate(this);
			//_bAction->Start();

			_lightNum = _lightIndex++;

			float lightPower = 0.7f;
			ZeroMemory(&_light, sizeof(D3DLIGHT9));	//초기화
			_light.Type = D3DLIGHT_POINT;		//라이트 타입
			_light.Ambient = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower); //광원 컬러값 설정
			_light.Diffuse = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower); //디퓨즈 값 (텍스쳐 원색)
			_light.Specular = D3DXCOLOR(lightPower, lightPower, lightPower, lightPower);// 빛이 모이는 곳. 정반사. 스뎅 번쩍
			_light.Position = GetWorldPosition();
			_light.Position.y += 1;
			_light.Range = 3;
			DEVICE->SetLight(_lightNum, &_light);	//라이트 디바이스에 셋팅
			DEVICE->LightEnable(_lightNum, false);		//라이트on,off 앞에 숫자는 라이트배열 이라고 보면 될듯.
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
				_light.Position = GetWorldPosition();
				DEVICE->SetLight(_lightNum, &_light);	//라이트 디바이스에 셋팅
				DEVICE->LightEnable(_lightNum, true);		//라이트on,off 앞에 숫자는 라이트배열 이라고 보면 될듯.

				SetScale(2, 2, 2);
			}
			else
			{
				if (m_pRootWoman != m_pRootSt) m_pRootWoman = m_pRootSt;
				DEVICE->LightEnable(_lightNum, false);		//라이트on,off 앞에 숫자는 라이트배열 이라고 보면 될듯.

				SetScale(1, 1, 1);
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
			_action = NULL;
		}

		void Click()
		{
			POINT m = GetMousePos();
			Ray r = GetRayByMousePos(m.x, m.y);

			Sphere s;
			s.position = GetLocalPosition() / 2;
			//s.y += 1;
			s.radius = 1;

			if (IntersectSphere(r, s))
			{
				_bAction->ClearPoint();
				_bAction->AddPoint(GetWorldPosition());
				_bAction->AddPoint(D3DXVECTOR3(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10)));
				_bAction->AddPoint(D3DXVECTOR3(RandomFloatRange(-10, 10), 0, RandomFloatRange(-10, 10)));
				_bAction->Start();
				SetAction(_bAction);
			}
		}

		void MoveTo(D3DXVECTOR3 d)
		{
			_bAction->ClearPoint();
			_bAction->AddPoint(GetWorldPosition());
			//_bAction->AddPoint({0, 0, 0});
			_bAction->AddPoint(d);
			_bAction->Start();
			SetAction(_bAction);
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
