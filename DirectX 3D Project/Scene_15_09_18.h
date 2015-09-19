#pragma once
#include "Scene.h"
#include "UIWindow.h"
#include "UITextBox.h"
#include "UIButton.h"

using namespace wakeup;
using namespace wakeup::Util;
using namespace wakeup::Objects;
using namespace wakeup::Util;
using namespace wakeup::Base;
using namespace wakeup::UI;

class Scene_15_09_18 : public Scene
{
private:
	Camera* _cam;
	UIWindow* _ui;
	//UITextBox* _ui2;
	//UIButton* _uiOk;
	//UIButton* _uiNo;

	LPD3DXSPRITE _sprite;

public:
	Scene_15_09_18();
	virtual ~Scene_15_09_18();

	HRESULT Setup();
	void Release();
	void Update(float timedelta);
	void Render();
};

class ButtonDeligate : public UIDeligate
{
protected:
	friend class UIWindow;

	POINT _clickDownPt;
	POINT _clickDownWindowPt;
	POINT _clickUpPt;
	POINT _clickUpWindowPt;
	POINT _prevClickPt;

	inline virtual UINT OnClickDown(UIWindow* caller, UIWindow* root) override
	{
		if (caller->GetTagNum() == 2)
		{
			UITextBox* t = (UITextBox*)root->GetWindowByTag(1);
			t->SetText("확인?");
		}
		else if (caller->GetTagNum() == 3)
		{
			UITextBox* t = (UITextBox*)root->GetWindowByTag(1);
			t->SetText("취소?");
		}
		else if (caller->GetTagNum() == 4)
		{
			root->SetHiddenState(true);
		}

		return RETURN_DEFAULT;
	}
	inline virtual UINT OnClickUp(UIWindow* caller, UIWindow* root) override
	{
		
		return RETURN_DEFAULT;
	}
	
};
