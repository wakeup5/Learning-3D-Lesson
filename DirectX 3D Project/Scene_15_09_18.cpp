#include "stdafx.h"
#include "Scene_15_09_18.h"


Scene_15_09_18::Scene_15_09_18()
{

}


Scene_15_09_18::~Scene_15_09_18()
{
}

HRESULT Scene_15_09_18::Setup()
{
	_cam = new Camera;
	_cam->SetWorldPosition({ 0, 5, 10 });

	_ui = new UIWindow;
	_ui->Setup();
	_ui->SetBackground("./resource/batman.png");
	_ui->SetSize(300, 500);
	_ui->SetPosition(10, 10);

	UITextBox* _ui2 = new UITextBox;
	_ui2->Setup();
	//_ui2->SetBackground(_tex, _info);
	_ui2->SetSize(200, 200);
	_ui2->SetPosition(50, 50);
	_ui2->AttachTo(_ui);
	_ui2->SetText("dlglglgldgldlgldlg鼇鼇鼇中中中中中中中中中中中中中中中中中中中中");
	_ui2->SetFontFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	_ui2->SetTagNum(1);

	UIButton* _uiOk = new UIButton;
	_uiOk->Setup();
	//_ui2->SetBackground(_tex, _info);
	_uiOk->SetSize(200, 50);
	_uiOk->SetPosition(50, 300);
	_uiOk->AttachTo(_ui);
	_uiOk->SetButtonTexture("./resource/batman.png", "./resource/batman.png", "./resource/batman.png");//"./resource/ui/btn-med-up.png", "./resource/ui/btn-med-over.png", "./resource/ui/btn-med-down.png");
	_uiOk->SetFontFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	_uiOk->SetText("�挫�");
	_uiOk->SetTagNum(2);
	
	UIButton* _uiNo = new UIButton;
	_uiNo->Setup();
	//_ui2->SetBackground(_tex, _info);
	_uiNo->SetSize(200, 50);
	_uiNo->SetPosition(50, 360);
	_uiNo->AttachTo(_ui);
	_uiNo->SetButtonTexture("./resource/batman.png", "./resource/batman.png", "./resource/batman.png");//"./resource/ui/btn-med-up.png", "./resource/ui/btn-med-over.png", "./resource/ui/btn-med-down.png");
	_uiNo->SetFontFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	_uiNo->SetText("鏃模");
	_uiNo->SetTagNum(3);

	UIButton* _uiclose = new UIButton;
	_uiclose->Setup();
	//_ui2->SetBackground(_tex, _info);
	_uiclose->SetSize(200, 50);
	_uiclose->SetPosition(50, 420);
	_uiclose->AttachTo(_ui);
	_uiclose->SetButtonTexture("./resource/ui/btn-med-up.png", "./resource/ui/btn-med-over.png", "./resource/ui/btn-med-down.png");
	_uiclose->SetFontFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	_uiclose->SetText("殘晦");
	_uiclose->SetTagNum(4);

	UIDeligate* del = new UIDeligateDefault;
	_ui->SetDeligate(del);

	UIDeligate* bd = new ButtonDeligate;
	_uiOk->SetDeligate(bd);
	_uiNo->SetDeligate(bd);
	_uiclose->SetDeligate(bd);

	D3DXCreateSprite(DEVICE, &_sprite);

	return S_OK;
}
void Scene_15_09_18::Release()
{
	SAFE_DELETE(_cam);
}
void Scene_15_09_18::Update(float timeDelta)
{
	_ui->Update();

	//_cam->LookPosition({ 0, 0, 0 });

	_cam->UpdateCamToDevice(DEVICE);

	if (!_ui->IsMouseOver() && GS.isMouseClick)
	{
		_cam->DefaultControl(timeDelta);
	}

	if (KEY_MGR->IsOnceDown('P'))
	{
		//static bool is = true;
		_ui->Toggle();
	}
}
void Scene_15_09_18::Render()
{
	GIZMO_MGR->WorldGrid(1, 10);
	
	_ui->Render(_sprite);
}