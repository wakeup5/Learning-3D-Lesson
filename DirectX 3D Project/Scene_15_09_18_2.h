#pragma once
#include "Scene.h"
#include "Cannon.h"
#include "Cube.h"

using namespace wakeup;
using namespace wakeup::Util;
using namespace wakeup::Objects;
using namespace wakeup::Util;
using namespace wakeup::Base;
//using namespace wakeup::UI;
using namespace wakeup::Objects::Cannons;


class Scene_15_09_18_2 : public Scene
{
private:
	Camera* _cam;

	Cannon* _c[10];
	Cube* _cube;

	std::vector<CannonBullet> _b;

	LPD3DXEFFECT pEffect;
public:
	Scene_15_09_18_2();
	virtual ~Scene_15_09_18_2();

	HRESULT Setup();
	void Release();
	void Update(float timedelta);
	void Render();
};

