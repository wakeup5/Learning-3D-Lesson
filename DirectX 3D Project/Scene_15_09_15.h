#pragma once
#include "Scene.h"
#include "cFrame.h"
#include "cAseLoader.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cObjMap.h"
#include "Cube.h"

class Scene_15_09_15 :
	public NS_ROOT::NS_BASE::Scene
{
private:
	NS_ROOT::NS_OBJECTS::Camera* _camera;
	cFrame* m_pRootFrame;

	D3DXVECTOR3 _posWoman;
	D3DXVECTOR3 _dirWoman;
	D3DXVECTOR3 _cRot;
	//맵
	std::vector<cGroup*> m_vecGroup;
	cObjMap* _om;

	//큐브즈
	NS_ROOT::NS_OBJECTS::Cube* _cubes[10];

	//텍스쳐들
	LPDIRECT3DTEXTURE9 _tex[3];

	int _score = 0;
public:
	Scene_15_09_15();
	virtual ~Scene_15_09_15();

	virtual HRESULT Setup();
	virtual void Release();
	virtual void Update(float timeDelta);
	virtual void Render();
};

