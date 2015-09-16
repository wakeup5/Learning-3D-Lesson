#include "stdafx.h"
#include "Charactor.h"

namespace NS_ROOT
{
	namespace NS_OBJECTS
	{
		Charactor::Charactor()
		{
			_root = new Cube;
			_root->Setup();
			_root->AttachTo(this);
		}


		Charactor::~Charactor()
		{
		}
		void Charactor::Release()
		{
			//_root->Release();
		}
		void Charactor::Update()
		{
			if (_action) _action->Update();
		}
		void Charactor::Render()
		{
			_root->Render();
		}
		void Charactor::OnActionFinish()
		{
			if (_action) _action->Start();
		}
	}
}