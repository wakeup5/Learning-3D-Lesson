#pragma once
#include "Scene.h"
#include "cFrame.h"
#include "cAseLoader.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cObjMap.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Charactor.h"
#include "ActionMoveBezier.h"

class Scene_15_09_15 :
	public NS_ROOT::NS_BASE::Scene
{
private:
	NS_ROOT::NS_OBJECTS::Camera* _camera;
	cFrame* m_pRootFrame;
	cFrame* m_pRootSt;
	cFrame* m_pRootRun;

	D3DXVECTOR3 _posWoman;
	D3DXVECTOR3 _dirWoman;
	D3DXVECTOR3 _cRot;
	D3DXVECTOR3 _look;
	//맵
	std::vector<cGroup*> m_vecGroup;
	cObjMap* _om;
	D3DXMATRIXA16 matWorld;

	//큐브즈
	NS_ROOT::NS_OBJECTS::Cube* _cubes[10];

	//텍스쳐들
	LPDIRECT3DTEXTURE9 _tex[3];

	int _score = 0;

	NS_ROOT::NS_OBJECTS::Pyramid* _bullets[10];


	//
	NS_ROOT::NS_OBJECTS::Charactor* _char;
	NS_ROOT::Objects::ActionMoveBezier* ac;

	LPDIRECT3DTEXTURE9 _tBat;
public:
	Scene_15_09_15();
	virtual ~Scene_15_09_15();

	virtual HRESULT Setup();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();

	void KeyControl();
	void CreateCube();
	void CreateBullet();
};

